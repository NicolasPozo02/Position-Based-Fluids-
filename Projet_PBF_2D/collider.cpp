#include "collider.h"

std::optional<StaticConstraint> PlanCollider::checkContact(const Particle& p)
{
    float C = dot(p.getExpectedPos()-pc,nc)-p.getRadius();

    if (C < 0)
    {
        return StaticConstraint{0,pc, nc, C};
    }
    return std::nullopt;
}

std::optional<StaticConstraint> SphereCollider::checkContact(const Particle& p)
{
    Vec2 diff = p.getPos() - center;
    float d = norm(diff);

    float C = d-(this->radius+p.getRadius());

    if (C<0)
    {
        Vec2 nc = diff*(1.0f/d);
        Vec2 pc = center + nc * this->radius;
        return StaticConstraint{0, pc, nc, C};
    }
    return std::nullopt;
}

void PlanCollider::draw(QPainter& painter)
{
    float scal = dot(nc,pc);
    painter.drawLine(static_cast<int>(pc[0]),static_cast<int>(pc[1]),0,static_cast<int>(scal/nc[1]));
}

void SphereCollider::draw(QPainter& painter)
{
    painter.drawEllipse(center[0]-radius,center[1]-radius, radius*2, radius *2);
}

