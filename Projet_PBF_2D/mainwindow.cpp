#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QPainter>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    draw_area_ = new DrawArea();
    this->ui->verticalLayout->addWidget(draw_area_);

    //Connexion unique du timer ici
    QObject::connect(timer, &QTimer::timeout, draw_area_, &DrawArea::animate);

    //Boutons
    QObject::connect(this->ui->  start_button,   &QPushButton::clicked, this, &MainWindow::start);
    QObject::connect(this->ui->   stop_button,   &QPushButton::clicked, this, &MainWindow::stop);
    QObject::connect(this->ui->restart_button,   &QPushButton::clicked, this, &MainWindow::restart);

    QObject::connect(ui->btn_generate, &QPushButton::clicked, this, [this]{
        int n = ui->sb_particleCount->value();
        draw_area_-> context.addRandomParticles(n);
        updateParticleCountLabel();
    });

    QObject::connect(ui->btn_generate, &QPushButton::clicked, draw_area_, &DrawArea::paint);

    //Sliders
    QObject::connect(ui->gravity_slider,    &QSlider::valueChanged, this, &MainWindow::gravitySlider_valueChanged);
    QObject::connect(ui->amplitude_slider,  &QSlider::valueChanged, this, &MainWindow::amplitudeSlider_valueChanged);
    QObject::connect(ui->coeffVorti_slider, &QSlider::valueChanged, this, &MainWindow::coeffVortiSlider_valueChanged);
    QObject::connect(ui->coeffVisco_slider, &QSlider::valueChanged, this, &MainWindow::coeffViscoSlider_valueChanged);
    QObject::connect(ui->k_scorr_slider,    &QSlider::valueChanged, this, &MainWindow::k_scorrSlider_valueChanged);

    // MAJ du compteur après ajout d'une particule par double clic sur l'écran.
    QObject::connect(draw_area_, &DrawArea::particleCountChanged, this, &MainWindow::updateParticleCountLabel);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::start(bool clicked)
{
    timer->start(16);
}

void MainWindow::stop(bool clicked)
{
    timer->stop();
}

void MainWindow::restart(bool clicked)
{
    timer->stop();
    draw_area_->resetSimulation();
}

void MainWindow::gravitySlider_valueChanged(int value)
{
    float newGravity = static_cast<float>(value);
    draw_area_->context.setGravity(newGravity);
    ui->gravity_label->setText(QString("Gravité : %1").arg(newGravity));
}

void MainWindow::amplitudeSlider_valueChanged(int value)
{
    float newAmplitude = static_cast<float>(value);
    draw_area_->context.setAmplitude(newAmplitude);
    ui->amplitude_label->setText(QString("Amplitude :%1").arg(newAmplitude));
}

void MainWindow::coeffVortiSlider_valueChanged(int value)
{
    float newVorti = static_cast<float>(value/100.0f);
    draw_area_->context.setCoeff_Vorti(newVorti);
    ui->coeffVorti_label->setText(QString("Vorticité : %1").arg(newVorti));
}

void MainWindow::coeffViscoSlider_valueChanged(int value)
{
    float newVisco = static_cast<float>(value/1000.0f);
    draw_area_->context.setCoeff_Visco(newVisco);
    ui->coeff_Visco_label->setText(QString("Viscosité : %1").arg(newVisco));
}

void MainWindow::k_scorrSlider_valueChanged(int value)
{
    float newK_scorr = static_cast<float>(value/100.f);
    draw_area_->context.setK_scorr(newK_scorr);
    ui->k_scorr_label->setText(QString("k_scorr : %1").arg(newK_scorr));
}


void MainWindow::updateParticleCountLabel()
{
    int count = draw_area_->context.particles.size();
    ui->count_label->setText(QString("Nombre de particules : %1").arg(count));
}

