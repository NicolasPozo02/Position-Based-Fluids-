#ifndef COLLIDER_H
#define COLLIDER_H

#include <QPainter>
#include <optional>
#include "constraints.h"
#include "particle.h"

class Collider //Classe parent pour les colliders.
{
public:
    Collider() = default;
    virtual ~Collider() = default;

    virtual std::optional<StaticConstraint> checkContact(const Particle& p) = 0; //Méthode pour déterminer le contact entre une particule et un collider
    virtual void draw(QPainter& painter) = 0;   //Méthode pour l'affichage des colliders
    virtual void setPc(const Vec2 newPc) = 0;
};

class PlanCollider : public Collider
{
    public:
    PlanCollider(Vec2 p, Vec2 n):pc(p),nc(n){}

    ~PlanCollider() override {};

    std::optional<StaticConstraint> checkContact(const Particle& p) override;

    void draw(QPainter& painter) override ;

    void setPc(const Vec2 newPc) override {pc = newPc;}

private:
    Vec2 pc;
    Vec2 nc;
};

class SphereCollider : public Collider
{
public:
    SphereCollider(Vec2 c, float r) : center(c), radius(r) {}

    ~SphereCollider() override{};

    std::optional<StaticConstraint> checkContact(const Particle& p) override;

    void  draw(QPainter& painter) override;
    void setPc(const Vec2 newPc) override {center = newPc;}

private:
    Vec2 center;
    float radius;
};

#endif // COLLIDER_H

