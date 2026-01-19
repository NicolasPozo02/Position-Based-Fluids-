#ifndef DRAWAREA_H
#define DRAWAREA_H

#include <QWidget>
#include "context.h"


class DrawArea : public QWidget
{
    Q_OBJECT

public:

    Context context;

    explicit DrawArea(QWidget *parent = nullptr);
    ~DrawArea() override {};

    void resizeEvent(QResizeEvent *event) override;

signals:

void particleCountChanged(int newCount);                        // Signal pour l'ajout d'une particule après un double clic sur l'écran

public slots:

    void paintEvent(QPaintEvent *event) override;               // Affichage des particules et des colliders
    void paint(bool clicked);                                   // Affichage des particules après avoir cliquer sur le bouton generate
    void mouseDoubleClickEvent(QMouseEvent *event) override;    // Ajout d'une particule par un double clic dans la zone d'affichage
    void animate();                                             // Animation de la simulation
    void resetSimulation();                                     // Restart de la simulation

};

#endif // DRAWAREA_H
