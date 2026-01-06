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

    QObject::connect(this->ui->start_button, &QPushButton::clicked, this, &MainWindow::start);
    QObject::connect(this->ui->stop_button, &QPushButton::clicked, this, &MainWindow::stop);
    QObject::connect(this->ui->restart_button, &QPushButton::clicked, this, &MainWindow::restart);

    QObject::connect(ui->gravity_slider, &QSlider::valueChanged, this, &MainWindow::gravitySlider_valueChanged);
    QObject::connect(ui->stiffness_slider, &QSlider::valueChanged, this, &MainWindow::stiffnessSlider_valueChanged);
    QObject::connect(ui->coeffSumR_slider, &QSlider::valueChanged, this, &MainWindow::coeffSumRSlider_valueChanged);
    QObject::connect(draw_area_, &DrawArea::particleCountChanged, this, &MainWindow::updateParticleCountLabel);

    QObject::connect(ui->btn_generate, &QPushButton::clicked, this, [this]{
        int n = ui->sb_particleCount->value();
        draw_area_-> context.addRandomParticles(n);
        updateParticleCountLabel();
    });

    QObject::connect(ui->btn_generate, &QPushButton::clicked, draw_area_, &DrawArea::paint);
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
    float newGravity = static_cast<float>(value); // Ou bien value /10.0f pour plus de précision
    draw_area_->context.setGravity(newGravity);
    ui->gravity_label->setText(QString("Gravité : %1").arg(newGravity));
}

void MainWindow::stiffnessSlider_valueChanged(int value)
{
    float newStiffness = static_cast<float>(value/100.0f);
    draw_area_->context.setStiffness(newStiffness);
    ui->stiffness_label->setText(QString("Raideur : %1").arg(newStiffness));
}

void MainWindow::coeffSumRSlider_valueChanged(int value)
{
    float newCoeffSumR = static_cast<float>(value/100.0f);
    draw_area_->context.setCoeffSumR(newCoeffSumR);
    ui->coeffSumR_label->setText(QString("Coefficient multiplicateur : %1").arg(newCoeffSumR));
}

void MainWindow::updateParticleCountLabel()
{
    int count = draw_area_->context.particles.size();
    ui->count_label->setText(QString("Nombre de particules : %1").arg(count));
}

