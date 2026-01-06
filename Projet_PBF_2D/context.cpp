#include <random>
#include <QDebug>
#include "context.h"

Context::Context()
{
    resetColliders();
}

void Context::resetColliders()
{
    colliders.clear();
    //Sol
    colliders.push_back(std::make_unique<PlanCollider>(Vec2(0,height),Vec2(0,-1)));
    //Plafond
    colliders.push_back(std::make_unique<PlanCollider>(Vec2(0,0),Vec2(0,1)));
    //Mur gauche
    colliders.push_back(std::make_unique<PlanCollider>(Vec2(0,0),Vec2(1,0)));
    //Mur droit
    colliders.push_back(std::make_unique<PlanCollider>(Vec2(width,0),Vec2(-1,0)));
    //Ajout d'un obstacle sphérique au milieu
    //colliders.push_back(std::make_unique<SphereCollider>(Vec2(width/2,height/2),40.0f));
}

void Context::addParticle(float x, float y)
{
    particles.push_back(std::make_unique<Particle>(x,y, 5.0f, 1.0f));
}

void Context::addRandomParticles(int count)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> disX(10.f, width - 10.0f);
    std::uniform_real_distribution<float> disY(10.f, height - 10.0f);

    for (int i = 0; i <count; i++)
    {
        addParticle(disX(gen),disY(gen));
    }
}

void Context::setGravity(const float g)
{
    this->gravity = g;
}

void Context::setStiffness(const float s)
{
    this->stiffness = s;
}

void Context::setCoeffSumR(const float coeff)
{
    this-> coeffSumR = coeff;
}

int Context::getHash(int ix, int iy) //Fonction de hachage spatial
{
    return (ix * 73856093) ^ (iy * 19349663);
}

void Context::updateGrid()
{
    spatialGrid.clear(); //On vide la grille à chaque frame

    for (int i = 0; i < (int)particles.size(); i++)
    {
        //Discrétisation : obtention des indices de case (ix,iy)
        int ix = static_cast<int>(std::floor(particles[i]->getExpectedPos()[0]/cellSize));
        int iy = static_cast<int>(std::floor(particles[i]->getExpectedPos()[1]/cellSize));
        int key = getHash(ix,iy);
        spatialGrid[key].push_back(i); // Rangement de l'index de la particule
    }
}


void Context::updatePhysicalSystem(float dt)
{
    itr++;

    for (auto &p : particles)
    {
        p->setState(CollisionState::None);
    }
    // 1. Prédiction (Gravité + Vitesse)
    for(int i = 0; i<this->particles.size();i++)
    {
            this->applyExternalForce(i);
            this->updateVelocity(dt,i);
            this->updateExpectedPosition(dt,i);
    }

    // 2. MAJ des voisins
    findNeighbors();

    // 3. Résolution des contraintes
    colliders[2]->setPc(Vec2(500.f*std::sin(dt*static_cast<float>(itr))*std::sin(dt*static_cast<float>(itr)),0.));
    for (int iter = 0; iter < 4; iter++)
    {
        // A. Collisions avec les murs
        addStaticContactConstraints();
        for (const auto&c : staticConstraints)
        {
            enforceStaticGroundConstraint(c,*particles[c.particle_index]);
        }

        // B. Calcul PBF
        computeLambdas();
        computeDeltaPositions();
    }

    // 4. Intégration finale

    for(int i=0; i < particles.size();i++)
    {
        this->updateVelocityAndPosition(dt,i);
    }
}

void Context::applyExternalForce(int i)
{
    this->particles[i]->setFext(Vec2(0.,this->particles[i]->getMass()*this->gravity)); //Gravité uniquement
}

void Context::updateVelocity(float dt, int i)
{
    Vec2 newVelocity = this->particles[i]->getVelocity()+this->particles[i]->getFext()*(dt/this->particles[i]->getMass());
    this->particles[i]->setVelocity(newVelocity);
}

void Context::updateExpectedPosition(float dt, int i)
{
    Vec2 newExpectedPosition = this->particles[i]->getPos()+this->particles[i]->getVelocity()*dt;
    this->particles[i]->setExpectedPos(newExpectedPosition);
}

void Context::addStaticContactConstraints()
{
    this->staticConstraints.clear(); //On vide les contraintes de la frame précédente. Pas de leak

    for (int i=0; i<particles.size();i++) //On itère sur chaque particule
    {
        for (auto& col : colliders) //Pour chaque particule, on appelle la méthode checkContact de tous les colliders
        {
            auto constraint = col->checkContact(*particles[i]);

            if (constraint.has_value())//Test si la "boîte" n'est pas vide
            {
                particles[i]->setState(CollisionState::Static);
                StaticConstraint c = constraint.value();
                c.particle_index = i; //Ajout de l'index de la particule.
                staticConstraints.push_back(c); //Ajout de la contrainte
            }
        }
    }
}

void Context::enforceStaticGroundConstraint(const StaticConstraint& c, Particle& p)
{
    Vec2 delta_p = c.nc * (-c.C);
    p.setExpectedPos(p.getExpectedPos()+delta_p);
}

void Context::updateVelocityAndPosition(float dt, int i)
{
    Particle& p = *particles[i];
    Vec2 newVel =(p.getExpectedPos()-p.getPos())*(1.0f/dt);
    p.setVelocity(newVel);
    p.setPos(p.getExpectedPos());
}

Vec2 Context::gradW(Vec2 r, float h)
{
    float dist = norm(r);
    if (dist < 0.001f || dist>=h) return Vec2(0,0);

    //Formule du Spiky Kernel Gradient
    float spiky = -45.0f /(M_PI * std::pow(h,6));
    float term = h - dist;
    float coeff = spiky * term * term;

    return (r * (1.0f / dist)) * coeff;
}

void Context::findNeighbors()
{
    updateGrid();
    for (int i=0; i < (int)particles.size(); i++)
    {
        particles[i]->neighbors.clear();
        Particle& p = *particles[i];

        // Obtention des coordonnées de la case de la particule A
        int ix = static_cast<int>(std::floor(p.getExpectedPos()[0]/cellSize));
        int iy = static_cast<int>(std::floor(p.getExpectedPos()[1]/cellSize));

        // Parcours de la case actuelle + les 8 cases voisines
        for (int nx = -1; nx<=1; nx++)
        {
            for (int ny = -1; ny <= 1; ny++)
            {
                int key = getHash(ix+nx,iy+ny);
                if (spatialGrid.count(key))
                {
                    for (int neighborIdx : spatialGrid[key])
                    {
                        if (i == neighborIdx)
                        {
                            continue;
                        }
                        float d2 = squaredLength(p.getExpectedPos()-particles[neighborIdx]->getExpectedPos());
                        if (d2 < cellSize * cellSize)
                        {
                            particles[i]->neighbors.push_back(neighborIdx);
                        }
                    }
                }
            }
        }
    }
}

void Context::computeLambdas()
{
    float h = cellSize;
    float h2 = h * h;
    float poly6 = 315.0f / (64.0f * M_PI * std::pow(h,9));
    float rho_0 = 2.91853e-05; // Densité de repos (à ajuster)
    float epsilon = 100.f; // Paramètre de relaxation pour éviter la division par zéro

    for (int i = 0; i < (int)particles.size(); i++)
    {
        Particle& pi = *particles[i];

        // 1. Calcul de la densité
        float rho_i = 0.0f;
        for (int j : pi.neighbors)
        {
            float r2 = squaredLength(pi.getExpectedPos()-particles[j]->getExpectedPos());
            if (r2 < h2)
            {
                float term = h2 - r2;
                rho_i += particles[j]->getMass() * poly6 * term * term * term;
            }
        }
        pi.density = rho_i;
        if (i == 0) { // On n'affiche que pour la première particule
            qDebug() << "Densité calculée : " << pi.density;
        }
        // 2. Calcul de la contrainte Ci
        float Ci = std::max(0.0f,(rho_i/rho_0)-1.0f);
        if (Ci <= 0.0f)
        {
            pi.lambda = 0.0f;
            continue;
        }

        // 3. Calcul du gradient (somme des carrés des gradients)
        float sum_grad_sq = 0.0f;
        Vec2 grad_pi_Ci(0,0);

        for (int j : pi.neighbors)
        {
            Vec2 r = pi.getExpectedPos() - particles[j]->getExpectedPos();
            Vec2 g = gradW(r,h); //Noyau Spiky à utiliser
            Vec2 grad_pj_Ci = g * (1.0f / rho_0);

            sum_grad_sq += squaredLength(grad_pj_Ci);// Contribution des voisins
            grad_pi_Ci += grad_pj_Ci;
        }

        sum_grad_sq += squaredLength(grad_pi_Ci);

        // 4. Calcul final du lambda
        pi.lambda = -Ci / (sum_grad_sq + epsilon);
    }
}

void Context::computeDeltaPositions()
{
    float rho_0 = 2.91853e-05;
    float h = cellSize;

    for(int i = 0; i < (int)particles.size(); ++i)
    {
        Particle& pi = *particles[i];
        Vec2 deltaP(0,0);

        for (int j : pi.neighbors)
        {
            Vec2 r = pi.getExpectedPos() - particles[j]->getExpectedPos();

            float scorr = 0.0f;

            deltaP += (pi.lambda + particles[j]->lambda + scorr) * gradW(r,h);
        }
        pi.deltaP = deltaP / rho_0;
        pi.setExpectedPos(pi.getExpectedPos()+pi.deltaP);
    }
}

