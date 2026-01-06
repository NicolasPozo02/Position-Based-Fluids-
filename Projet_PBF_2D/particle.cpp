#include "particle.h"

Particle::Particle(float x, float y, float r, float m): pos(x,y), radius(r), mass(m){};

void Particle::setPos(const Vec2 newPos)
{
    this->pos = newPos;
}

void Particle::setVelocity(const Vec2 newVelocity)
{
    this->velocity = newVelocity;
}

void Particle::setFext(const Vec2 newFext)
{
    this->Fext = newFext;
}

void Particle::setExpectedPos(const Vec2 newExpectedPos)
{
    this->expectedPos = newExpectedPos;
}

void Particle::setState(const CollisionState newState)
{
    this->state = newState;
}

void Particle::setDensity(const float newDensity)
{
    this->density = newDensity;
}
