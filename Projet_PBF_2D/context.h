#ifndef CONTEXT_H
#define CONTEXT_H
#include <memory>
#include <unordered_map>
#include "collider.h"

class Context
{

public:

    std::vector<std::unique_ptr<Particle>> particles;
    std::vector<std::unique_ptr<PlanCollider>> colliders;       //Vecteur de pointeurs
    std::vector<StaticConstraint> staticConstraints;
    std::vector<ParticleConstraint> particleConstraints;

    //Table de hachage
    //Clé : index de la case (int)
    //Valeur : liste des indices des particules dans cette case

    std::unordered_map<int, std::vector<int>> spatialGrid;

    float gravity;                                          //Définition de la gravité
    float stiffness;
    float coeffSumR;
    float dt = 0.016f;                                      //Pas de temps
    float cellSize = 20.0f;                                         //2x le rayon des particules est un bon choix
    float height;
    float width;
    int itr = 0;

    Context();
    ~Context()=default;

    void updatePhysicalSystem(float dt);
    void resetColliders();
    void addParticle(float x, float y);
    void addRandomParticles(int count);

    float getGravity() const {return gravity;}
    void setGravity(const float g);

    float getStiffness() const {return stiffness;}
    void setStiffness(const float s);

    float getCoeffSumR() const {return coeffSumR;}
    void setCoeffSumR(const float coeff);

private:

    //Méthodes pour les principales étapes de la simulation
    void applyExternalForce(int i);
    void updateVelocity(float dt, int i);
    void updateExpectedPosition(float dt, int i);
    void addStaticContactConstraints();
    void addDynamicContactConstraints();
    void enforceStaticGroundConstraint(const StaticConstraint& constraint, Particle& p);
    void enforceParticleConstraint(const ParticleConstraint& constraint);
    void projectConstraints();
    void updateVelocityAndPosition(float dt, int i);
    void applyFriction(float dt);
    float computeDensity(int i);
    void computeLambdas();
    void computeDeltaPositions();
    Vec2 gradW(Vec2 r, float h);

    //Méthodes pour la table de hachage
    void updateGrid();
    int getHash(int ix, int iy);
    void findNeighbors();
};

#endif // CONTEXT_H
