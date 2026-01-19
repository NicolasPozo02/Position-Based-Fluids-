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
    Vec2 diff = p.getExpectedPos() - center;
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
    // 1. Définir le vecteur direction (perpendiculaire à la normale)

    Vec2 direction(-nc[1], nc[0]);

    // 2. Créer deux points très éloignés pour simuler une ligne "infinie"

    float length = 2000.0f; // Assez grand pour couvrir tout l'écran
    Vec2 p1 = pc + direction * length;
    Vec2 p2 = pc - direction * length;


    // 4. Dessiner la ligne
    painter.drawLine(p1[0], p1[1], p2[0], p2[1]);
}


void  SphereCollider::draw(QPainter& painter)
{
    painter.drawEllipse(center[0]-radius,center[1]-radius, radius*2, radius *2);
}

