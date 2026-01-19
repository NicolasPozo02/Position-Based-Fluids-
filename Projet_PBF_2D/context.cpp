#include <random>
#include <QDebug>
#include <QtConcurrent>
#include "context.h"

Context::Context()
{
    resetColliders();
}

void Context::resetColliders()
{
    colliders.clear();
    //Sol
    colliders.push_back(std::make_unique<PlanCollider>(PlanCollider(Vec2(0,height),Vec2(0,-1))));
    //Plafond
    colliders.push_back(std::make_unique<PlanCollider>(PlanCollider(Vec2(0,0),Vec2(0,1))));
    //Mur gauche
    colliders.push_back(std::make_unique<PlanCollider>(PlanCollider(Vec2(0,0),Vec2(1,0))));
    //Mur droit
    colliders.push_back(std::make_unique<PlanCollider>(PlanCollider(Vec2(width,0),Vec2(-1,0))));
    //Ajout d'un obstacle sphérique au milieu
    colliders.push_back(std::make_unique<SphereCollider>(SphereCollider(Vec2(width/2,height/2),50.0f)));
}

void Context::addParticle(float x, float y)
{
    particles.push_back(Particle(x,y, rayon, masse));
}

void Context::addRandomParticles(int count)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> disX(rayon*2, width - (rayon*2));
    std::uniform_real_distribution<float> disY(rayon*2, height - (rayon*2));

    for (int i = 0; i <count; i++)
    {
        addParticle(disX(gen),disY(gen));
    }
}

int Context::getHash(int ix, int iy)
{
    return (ix * 73856093) ^ (iy * 19349663);
}

void Context::updateGrid()
{
    spatialGrid.clear(); //On vide la grille à chaque frame

    for (int i = 0; i < (int)particles.size(); i++)
    {
        //Discrétisation : obtention des indices de case (ix,iy)
        int ix = static_cast<int>(std::floor(particles[i].getExpectedPos()[0]/cellSize));
        int iy = static_cast<int>(std::floor(particles[i].getExpectedPos()[1]/cellSize));
        int key = getHash(ix,iy);
        spatialGrid[key].push_back(i); // Rangement de l'index de la particule
    }
}

float Context::computePoly6(float r, float h)
{
    if (r < 0 || r > h) return 0.0f;
    float h2 = h * h;
    float r2 = r * r;
    float term = h2 - r2;
    float alpha = 4.f / (M_PI * std::pow(h,8));
    return alpha * term * term * term;
}

Vec2 Context::gradW(Vec2 r_vec, float h)
{
    float r = norm(r_vec);
    if (r <= 0.001f || r>=h) return Vec2(0,0);
    float spiky = -30.0f /(M_PI * std::pow(h,5));
    float term = h - r;
    float grad_mag = spiky * term * term;

    return (r_vec * (1.0f / r)) * grad_mag;
}

void Context::updatePhysicalSystem(float dt)
{
    itr++;

    for (auto &p : particles)
    {
        p.setState(CollisionState::None);
    }
    // 1. Prédiction
    for(int i = 0; i<this->particles.size();i++)
    {
            this->applyExternalForce(i);
            this->updateVelocity(dt,i);
            this->updateExpectedPosition(dt,i);
    }

    // 2. MAJ des voisins
    findNeighbors();

    // 3. Résolution des contraintes
    colliders[2]->setPc(Vec2(amplitude*std::sin(dt*static_cast<float>(itr))*std::sin(dt*static_cast<float>(itr)),0.));
    colliders[3]->setPc(Vec2(width-amplitude*std::sin(dt*static_cast<float>(itr))*std::sin(dt*static_cast<float>(itr)),0.));
    for (int iter = 0; iter < 4; iter++)
    {
        // A. Collisions avec les murs
        addStaticContactConstraints();
        for (const auto&c : staticConstraints)
        {
            enforceStaticGroundConstraint(c,particles[c.particle_index]);
        }

        // B. Calcul PBF
        computeLambdas();
        computeDeltaPositions();

        for (int i = 0 ;  i<particles.size(); i++)
        {
            updatePbfPosition(dt, i);
        }
    }

    // 4. Intégration finale

    for(int i=0; i < particles.size();i++)
    {
        updateVelocity2(dt,i);
    }

    applyVorticityAndViscosity(dt);

    for (int i = 0 ;  i<particles.size(); i++)
    {
        updateFinalPosition(dt,i);
    }
}

// 1. Prédiction

void Context::applyExternalForce(int i)
{
    this->particles[i].setFext(Vec2(0.,this->particles[i].getMass()*this->gravity));
}

void Context::updateVelocity(float dt, int i)
{
    Vec2 newVelocity = this->particles[i].getVelocity()+this->particles[i].getFext()*(dt/this->particles[i].getMass());
    this->particles[i].setVelocity(newVelocity);
}

void Context::updateExpectedPosition(float dt, int i)
{
    Vec2 newExpectedPosition = this->particles[i].getPos()+this->particles[i].getVelocity()*dt;
    this->particles[i].setExpectedPos(newExpectedPosition);
}

// 2. MAJ des voisins

void Context::findNeighbors()
{
    updateGrid();
    for (int i=0; i < (int)particles.size(); i++)
    {
        particles[i].neighbors.clear();
        Particle& p = particles[i];

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
                        float d2 = squaredLength(p.getExpectedPos()-particles[neighborIdx].getExpectedPos());
                        if (d2 < cellSize * cellSize)
                        {
                            particles[i].neighbors.push_back(neighborIdx);
                        }
                    }
                }
            }
        }
    }
}

// 3. Résolution des contraintes

void Context::addStaticContactConstraints()
{
    this->staticConstraints.clear(); //On vide les contraintes de la frame précédente.

    for (int i=0; i<particles.size();i++)
    {
        for (auto& col : colliders)
        {
            auto constraint = col->checkContact(particles[i]);

            if (constraint.has_value())
            {
                StaticConstraint c = constraint.value();
                c.particle_index = i;                       //Ajout de l'index de la particule.
                staticConstraints.push_back(c);             //Ajout de la contrainte
                particles[i].setState(CollisionState::Static);
            }
        }
    }
}

void Context::enforceStaticGroundConstraint(const StaticConstraint& c, Particle& p)
{
    Vec2 delta_p = c.nc * (-c.C);
    p.setExpectedPos(p.getExpectedPos()+delta_p);
}

void Context::computeLambdas()
{
    float h = cellSize;

    for (int i = 0; i < (int)particles.size(); i++)
    {
        Particle& pi = particles[i];

        // 1. Calcul de la densité
        float rho_i = 0.0f;
        for (int j : pi.neighbors)
        {
            float r = norm(pi.getExpectedPos()-particles[j].getExpectedPos());
            rho_i += particles[j].getMass()*computePoly6(r,h);
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

        // 3. Calcul du gradient
        float sum_grad_sq = 0.0f;
        Vec2 grad_pi_Ci(0,0);

        for (int j : pi.neighbors)
        {
            Vec2 r_vec = pi.getExpectedPos() - particles[j].getExpectedPos();
            Vec2 g = gradW(r_vec,h);
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
    float h = cellSize;

    float w_dq = computePoly6(dq_dist_scorr,h);

    for(int i = 0; i < (int)particles.size(); ++i)
    {
        Particle& pi = particles[i];
        Vec2 deltaP(0,0);

        for (int j : pi.neighbors)
        {
            Vec2 r_vec = pi.getExpectedPos() - particles[j].getExpectedPos();
            float r = norm(r_vec);

            if (r < h && r > 0)
            {
                // Calcul de scorr (pression artificielle)
                float w_r = computePoly6(r,h);
                float scorr = -k_scorr * std::pow(w_r/w_dq, n_scorr);

                deltaP += (pi.lambda + particles[j].lambda + scorr) * gradW(r_vec,h);
            }
        }
        pi.deltaP = deltaP / rho_0;
    }

}

void Context::updatePbfPosition(float dt, int i)
{
    Particle& p = particles[i];
    p.setExpectedPos(p.getExpectedPos()+p.deltaP);
}

// 4. Intégration finale

void Context::updateVelocity2(float dt, int i)
{
    Particle& p = particles[i];
    Vec2 newVel =(p.getExpectedPos()-p.getPos())*(1.0f/dt);
    p.setVelocity(newVel);
}

void Context::applyVorticityAndViscosity(float dt)
{
    int n = particles.size();
    std::vector<Vec2> omegas(n, Vec2(0,0));
    std::vector<float> omega_mag(n,0.0f);
    float h = cellSize;

    // 1. Calcul de la vorticité locale pour chaque particule
    for (int i = 0; i < n ; i++)
    {
        Vec2 curl(0,0);
        for (int j : particles[i].neighbors)
        {
            Vec2 v_ij = particles[j].getVelocity() - particles[i].getVelocity();
            Vec2 grad = gradW(particles[i].getExpectedPos() - particles[j].getExpectedPos(),h);
            omega_mag[i] += (v_ij[0]*grad[1]-v_ij[1]*grad[0]);
        }
    }

    // 2. Appliquer la force de vorticité et la viscosité XSPH
    for (int i = 0; i < n; i++)
    {
        Vec2 eta(0,0);
        for (int j : particles[i].neighbors)
        {
            float mag_diff = std::abs(omega_mag[j]) - std::abs(omega_mag[i]);
            eta+=mag_diff*gradW(particles[i].getExpectedPos()-particles[j].getExpectedPos(),h);
        }
        if (norm(eta) > 0.001f)
        {
            Vec2 N = eta/norm(eta);
            Vec2 vorticityForce = c_vorti * Vec2(N[1]*omega_mag[i], -N[0]*omega_mag[i]);
            particles[i].setVelocity(particles[i].getVelocity()+dt * vorticityForce);
        }
        Vec2 sum_visco(0,0);
        for (int j : particles[i].neighbors)
        {
            Vec2 v_ij = particles[j].getVelocity() - particles[i].getVelocity();
            float r = norm(particles[i].getExpectedPos() - particles[j].getExpectedPos());
            float w_ij = computePoly6(r,h);
            sum_visco += v_ij * w_ij;
        }
        particles[i].setVelocity(particles[i].getVelocity() + c_visco * sum_visco);
    }
}

void Context::updateFinalPosition(float dt, int i)
{
    Particle& p = particles[i];
    Vec2 newVel =(p.getExpectedPos()-p.getPos())*(1.0f/dt);
    p.setVelocity(newVel);
    p.setPos(p.getExpectedPos());
}



