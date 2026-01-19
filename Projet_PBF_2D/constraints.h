#ifndef CONSTRAINTS_H
#define CONSTRAINTS_H
#include "vec2.h"

struct StaticConstraint // Structure pour la définition des contraintes avec les colliders.
{
    int particle_index; //Indice de la particule impliquée dans le contact.
    Vec2 pc;
    Vec2 nc;
    float C;
};

#endif // CONSTRAINTS_H
