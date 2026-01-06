#ifndef CONSTRAINTS_H
#define CONSTRAINTS_H
#include "vec2.h"

struct StaticConstraint
{
    int particle_index;
    Vec2 pc;
    Vec2 nc;
    float C;
};

struct ParticleConstraint
{
    int particle_i;
    int particle_j;
    Vec2 ni;            // Normale de collision
    float C;            // Pénétration
};

#endif // CONSTRAINTS_H
