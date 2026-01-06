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
    Q_OBJECT                                // macro autorisant slot et signals

public:

    MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

public slots:

    void start(bool clicked);
    void stop(bool clicked);
    void restart(bool clicked);

private slots:

    void gravitySlider_valueChanged(int value);
    void stiffnessSlider_valueChanged(int value);
    void coeffSumRSlider_valueChanged(int value);
    void updateParticleCountLabel();

private:

    Ui::MainWindow* ui;
    DrawArea* draw_area_;
    QTimer* timer = new QTimer();
};

#endif // MAINWINDOW_H
