#include "drawarea.h"
#include <QPainter>
#include <QMouseEvent>

DrawArea::DrawArea(QWidget *parent)
    : QWidget{parent}
{
    //setFixedSize(static_cast<int>(context.width),static_cast<int>(context.height));
}

void DrawArea::resetSimulation()
{
    context.particles.clear();
    context.resetColliders();
    update();
}

void DrawArea::resizeEvent(QResizeEvent *event)
{
    context.width = static_cast<float>(this->width());
    context.height = static_cast<float>(this->height());
    context.resetColliders();
    QWidget::resizeEvent(event);
}

void DrawArea::paintEvent(QPaintEvent *event)
{
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing);

    p.setPen(Qt::green);
    p.setBrush(Qt::green);
    for (const auto& col : context.colliders)
    {
        col->draw(p);
    }

    for (const auto& i : context.particles)
    {
        if (i->getState() == CollisionState::Static)
        {
            p.setPen(Qt::black);
            p.setBrush(Qt::black);
        }
        else if (i->getState() == CollisionState::Particle)
        {
            p.setPen(QColor(255, 165, 0));
            p.setBrush(QColor(255, 165, 0));
        }
        else
        {
            p.setPen(Qt::blue);
            p.setBrush(Qt::blue);
        }
        Vec2 pos = i->getPos();
        if (std::isnan(pos[0])||std::isnan(pos[1])) continue;
        //QRectF target(i->getPos()[0]-(i->getRadius()*4),i->getPos()[1]-i->getRadius()*4),i->getRadius()*2,i->getRadius()*2);
        p.drawEllipse(i->getPos()[0],i->getPos()[1],i->getRadius()*4,i->getRadius()*4);
    }
}

void DrawArea::paint(bool clicked)
{
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing);

    p.setPen(Qt::black);
    p.setBrush(Qt::black);
    for (const auto& col : context.colliders)
    {
        col->draw(p);
    }
    p.setPen(Qt::red);
    p.setBrush(QBrush(Qt::red));
    for (const auto& i : context.particles)
    {
        Vec2 pos = i->getPos();
        if (std::isnan(pos[0])||std::isnan(pos[1])) continue;
        QRectF target(i->getPos()[0]-i->getRadius(),i->getPos()[1]-i->getRadius(),i->getRadius()*2,i->getRadius()*2);
        p.drawEllipse(target);
    }
    update();
}

void DrawArea::mouseDoubleClickEvent(QMouseEvent *event)
{
    context.addParticle(event->position().x(), event->position().y());
    emit particleCountChanged(static_cast<int>(context.particles.size()));
    update();
}

void DrawArea::animate()
{
    this->context.updatePhysicalSystem(this->context.dt);
    update();
}
