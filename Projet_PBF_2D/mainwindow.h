#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "drawarea.h"
#include <QMainWindow>
#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class DrawArea;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

public slots:

    void start(bool clicked);       // Lancement de la simulaiton
    void stop(bool clicked);        // Pause de la simulation
    void restart(bool clicked);     // Lancement d'une nouvelle simulation

private slots:

    // METHODES POUR MODIFIER LES VALEURS DISPOSANT D'UN QSLIDER

    void gravitySlider_valueChanged(int value);
    void amplitudeSlider_valueChanged(int value);
    void coeffVortiSlider_valueChanged(int value);
    void coeffViscoSlider_valueChanged(int value);
    void k_scorrSlider_valueChanged(int value);

    // MISE A JOUR DU COMPTEUR DE PARTICULES

    void updateParticleCountLabel();

private:

    Ui::MainWindow* ui;
    DrawArea* draw_area_;
    QTimer* timer = new QTimer();
};

#endif // MAINWINDOW_H
