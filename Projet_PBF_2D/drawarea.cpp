#include "drawarea.h"
#include <QPainter>
#include <QMouseEvent>

DrawArea::DrawArea(QWidget *parent)
    : QWidget{parent}{}

void DrawArea::resetSimulation()
{
    context.particles.clear();
    context.itr = 0;
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

/*void DrawArea::paintEvent(QPaintEvent *event)
{
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing);

    p.setPen(Qt::green);
    p.setBrush(Qt::green);
    for (auto& col : context.colliders)
    {
        col->draw(p);
    }

    for (const auto& i : context.particles)
    {
        if (i.getState() == CollisionState::Static)
        {
            p.setPen(Qt::black);
            p.setBrush(Qt::black);
        }
        else
        {
            p.setPen(Qt::blue);
            p.setBrush(Qt::blue);
        }
        Vec2 pos = i.getPos();
        if (std::isnan(pos[0])||std::isnan(pos[1])) continue;
        p.drawEllipse(i.getPos()[0],i.getPos()[1],i.getRadius(),i.getRadius());
    }
}*/

void DrawArea::paint(bool clicked)
{
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing);

    p.setPen(Qt::black);
    p.setBrush(Qt::black);
    for (auto& col : context.colliders)
    {
        col->draw(p);
    }
    p.setPen(Qt::blue);
    p.setBrush(QBrush(Qt::blue));
    for (const auto& i : context.particles)
    {
        Vec2 pos = i.getPos();
        if (std::isnan(pos[0])||std::isnan(pos[1])) continue;
        p.drawEllipse(i.getPos()[0],i.getPos()[1],i.getRadius(),i.getRadius());
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

QImage createDensityBrush(int size) {
    QImage brush(size, size, QImage::Format_RGBA8888);
    brush.fill(Qt::transparent);
    QPainter p(&brush);

    QRadialGradient grad(size/2, size/2, size/2);
    // On utilise le canal Alpha pour stocker la "densité"
    grad.setColorAt(0, QColor(0, 0, 0, 255)); // Densité max au centre
    grad.setColorAt(1, QColor(0, 0, 0, 0));   // Densité nulle au bord

    p.setBrush(grad);
    p.setPen(Qt::NoPen);
    p.drawEllipse(0, 0, size, size);
    return brush;
}

void DrawArea::paintEvent(QPaintEvent *event) {
    QPainter finalPainter(this);
    finalPainter.setRenderHint(QPainter::Antialiasing);

    // 1. Créer la carte de densité (on utilise ARGB pour que CompositionMode_Plus fonctionne bien)
    QImage densityMap(size(), QImage::Format_ARGB32);
    densityMap.fill(Qt::transparent); // Important : remplir de vide (alpha 0)

    QPainter imgPainter(&densityMap);
    // Ce mode permet d'additionner les valeurs alpha quand les pinceaux se chevauchent
    imgPainter.setCompositionMode(QPainter::CompositionMode_Plus);

    // Taille de l'influence visuelle (plus c'est grand, plus l'eau est visqueuse)
    int brushSize = 32;
    static QImage brush = createDensityBrush(brushSize);

    // 2. Dessiner l'influence de chaque particule
    for (const auto& part : context.particles) {
        // On centre le pinceau sur la position de la particule
        imgPainter.drawImage(part.getPos()[0] - brushSize/2,
                             part.getPos()[1] - brushSize/2,
                             brush);
    }
    imgPainter.end();

    // 3. Post-traitement : Thresholding (Seuillage)
    // On transforme les zones denses en "eau" et le reste en transparent
    QImage finalImage(size(), QImage::Format_ARGB32);
    finalImage.fill(Qt::transparent);

    for (int y = 0; y < densityMap.height(); ++y) {
        QRgb *srcLine = reinterpret_cast<QRgb*>(densityMap.scanLine(y));
        QRgb *destLine = reinterpret_cast<QRgb*>(finalImage.scanLine(y));

        for (int x = 0; x < densityMap.width(); ++x) {
            int alpha = qAlpha(srcLine[x]);

            if (alpha < 100) continue; // Trop peu dense, on laisse transparent

            if (alpha > 100 && alpha < 130) {
                // ZONE ÉCUME : Transition du transparent vers le blanc/bleu ciel
                float t = (alpha - 100) / 30.0f;
                destLine[x] = qRgba(200, 235, 255, t * 255);
            }
            else if (alpha >= 130) {
                // ZONE EAU : Transition du bleu ciel vers le bleu profond
                float t = std::min(1.0f, (alpha - 130) / 100.0f);
                int r = 200 + t * (0 - 200);
                int g = 235 + t * (100 - 235);
                int b = 255 + t * (230 - 255);
                destLine[x] = qRgba(r, g, b, 240); // 240 pour une légère transparence
            }
        }
    }

    // 4. Affichage final
    finalPainter.drawImage(0, 0, finalImage);

    // 5. Dessiner les colliders par-dessus
    finalPainter.setPen(Qt::green);
    finalPainter.setBrush(Qt::green);
    for (auto& col : context.colliders)
    {
        col->draw(finalPainter);
    }
}
