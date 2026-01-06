#ifndef PARTICLE_H
#define PARTICLE_H

#include<vector>
#include "vec2.h"

enum class CollisionState {None, Static, Particle};

class Particle
{
public:

    Particle(float x, float y, float r, float m);

    Vec2 getPos() const {return pos;}
    void setPos(const Vec2 newPos);

    Vec2 getVelocity() const {return velocity;}
    void setVelocity(const Vec2 newVelocity);

    Vec2 getFext() const {return Fext;}
    void setFext(const Vec2 newFext);

    Vec2 getExpectedPos() const {return expectedPos;}
    void setExpectedPos(const Vec2 newExpectedPos);

    float getRadius() const {return radius;}
    float getMass()const {return mass;}

    CollisionState getState() const {return state;}
    void setState(const CollisionState newState);

    float getDensity() const {return density;}
    void setDensity(const float newDensity);

    std::vector<int> getNeighbors() const {return neighbors;}
    void setNeighbors(const std::vector<int> newNeighbors);

    std::vector<int> neighbors;
    float lambda = 0.0f;
    float density = 0.0f;
    Vec2 deltaP = Vec2(0.0f,0.0f);

private:
    Vec2 pos;
    Vec2 expectedPos;
    Vec2 velocity;
    Vec2 Fext;
    CollisionState state = CollisionState::None; // Etat par défaut
    float radius;
    float mass;
};

#endif // PARTICLE_H
