/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_2;
    QVBoxLayout *verticalLayout_4;
    QPushButton *start_button;
    QPushButton *stop_button;
    QPushButton *restart_button;
    QVBoxLayout *verticalLayout_5;
    QLabel *count_label;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *btn_generate;
    QSpinBox *sb_particleCount;
    QVBoxLayout *verticalLayout_6;
    QHBoxLayout *horizontalLayout_4;
    QLabel *amplitude_label;
    QSlider *amplitude_slider;
    QHBoxLayout *horizontalLayout_5;
    QHBoxLayout *horizontalLayout_6;
    QLabel *gravity_label;
    QSlider *gravity_slider;
    QVBoxLayout *verticalLayout_9;
    QVBoxLayout *verticalLayout_7;
    QHBoxLayout *horizontalLayout_7;
    QLabel *coeffVorti_label;
    QSlider *coeffVorti_slider;
    QHBoxLayout *horizontalLayout_8;
    QLabel *coeff_Visco_label;
    QSlider *coeffVisco_slider;
    QHBoxLayout *horizontalLayout_9;
    QLabel *k_scorr_label;
    QSlider *k_scorr_slider;
    QVBoxLayout *verticalLayout_3;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(800, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName("verticalLayout");
        groupBox = new QGroupBox(centralwidget);
        groupBox->setObjectName("groupBox");
        groupBox->setMinimumSize(QSize(0, 0));
        groupBox->setMaximumSize(QSize(16777215, 16777215));
        groupBox->setSizeIncrement(QSize(0, 0));
        groupBox->setBaseSize(QSize(0, 0));
        verticalLayout_2 = new QVBoxLayout(groupBox);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout_2->setSizeConstraint(QLayout::SizeConstraint::SetFixedSize);
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        horizontalLayout_2->setSizeConstraint(QLayout::SizeConstraint::SetDefaultConstraint);
        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName("verticalLayout_4");
        verticalLayout_4->setContentsMargins(5, -1, 5, -1);
        start_button = new QPushButton(groupBox);
        start_button->setObjectName("start_button");
        start_button->setEnabled(true);
        start_button->setIconSize(QSize(12, 12));

        verticalLayout_4->addWidget(start_button);

        stop_button = new QPushButton(groupBox);
        stop_button->setObjectName("stop_button");

        verticalLayout_4->addWidget(stop_button);

        restart_button = new QPushButton(groupBox);
        restart_button->setObjectName("restart_button");

        verticalLayout_4->addWidget(restart_button);


        horizontalLayout_2->addLayout(verticalLayout_4);

        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setObjectName("verticalLayout_5");
        verticalLayout_5->setContentsMargins(5, -1, 5, -1);
        count_label = new QLabel(groupBox);
        count_label->setObjectName("count_label");
        count_label->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout_5->addWidget(count_label);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        btn_generate = new QPushButton(groupBox);
        btn_generate->setObjectName("btn_generate");

        horizontalLayout_3->addWidget(btn_generate);

        sb_particleCount = new QSpinBox(groupBox);
        sb_particleCount->setObjectName("sb_particleCount");
        sb_particleCount->setMaximum(100000);

        horizontalLayout_3->addWidget(sb_particleCount);


        verticalLayout_5->addLayout(horizontalLayout_3);


        horizontalLayout_2->addLayout(verticalLayout_5);

        verticalLayout_6 = new QVBoxLayout();
        verticalLayout_6->setObjectName("verticalLayout_6");
        verticalLayout_6->setContentsMargins(5, -1, -1, -1);
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        amplitude_label = new QLabel(groupBox);
        amplitude_label->setObjectName("amplitude_label");

        horizontalLayout_4->addWidget(amplitude_label);

        amplitude_slider = new QSlider(groupBox);
        amplitude_slider->setObjectName("amplitude_slider");
        QSizePolicy sizePolicy(QSizePolicy::Policy::MinimumExpanding, QSizePolicy::Policy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(amplitude_slider->sizePolicy().hasHeightForWidth());
        amplitude_slider->setSizePolicy(sizePolicy);
        amplitude_slider->setMaximum(1000);
        amplitude_slider->setOrientation(Qt::Orientation::Horizontal);

        horizontalLayout_4->addWidget(amplitude_slider);


        verticalLayout_6->addLayout(horizontalLayout_4);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName("horizontalLayout_5");
        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName("horizontalLayout_6");
        gravity_label = new QLabel(groupBox);
        gravity_label->setObjectName("gravity_label");

        horizontalLayout_6->addWidget(gravity_label);

        gravity_slider = new QSlider(groupBox);
        gravity_slider->setObjectName("gravity_slider");
        gravity_slider->setMaximum(1000);
        gravity_slider->setOrientation(Qt::Orientation::Horizontal);

        horizontalLayout_6->addWidget(gravity_slider);


        horizontalLayout_5->addLayout(horizontalLayout_6);


        verticalLayout_6->addLayout(horizontalLayout_5);


        horizontalLayout_2->addLayout(verticalLayout_6);

        verticalLayout_9 = new QVBoxLayout();
        verticalLayout_9->setObjectName("verticalLayout_9");

        horizontalLayout_2->addLayout(verticalLayout_9);

        verticalLayout_7 = new QVBoxLayout();
        verticalLayout_7->setObjectName("verticalLayout_7");
        verticalLayout_7->setContentsMargins(5, -1, -1, -1);
        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName("horizontalLayout_7");
        horizontalLayout_7->setContentsMargins(10, -1, -1, -1);
        coeffVorti_label = new QLabel(groupBox);
        coeffVorti_label->setObjectName("coeffVorti_label");

        horizontalLayout_7->addWidget(coeffVorti_label);

        coeffVorti_slider = new QSlider(groupBox);
        coeffVorti_slider->setObjectName("coeffVorti_slider");
        coeffVorti_slider->setMaximum(100);
        coeffVorti_slider->setOrientation(Qt::Orientation::Horizontal);

        horizontalLayout_7->addWidget(coeffVorti_slider);


        verticalLayout_7->addLayout(horizontalLayout_7);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setObjectName("horizontalLayout_8");
        coeff_Visco_label = new QLabel(groupBox);
        coeff_Visco_label->setObjectName("coeff_Visco_label");

        horizontalLayout_8->addWidget(coeff_Visco_label);

        coeffVisco_slider = new QSlider(groupBox);
        coeffVisco_slider->setObjectName("coeffVisco_slider");
        coeffVisco_slider->setMaximum(1000);
        coeffVisco_slider->setOrientation(Qt::Orientation::Horizontal);

        horizontalLayout_8->addWidget(coeffVisco_slider);


        verticalLayout_7->addLayout(horizontalLayout_8);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setObjectName("horizontalLayout_9");
        k_scorr_label = new QLabel(groupBox);
        k_scorr_label->setObjectName("k_scorr_label");

        horizontalLayout_9->addWidget(k_scorr_label);

        k_scorr_slider = new QSlider(groupBox);
        k_scorr_slider->setObjectName("k_scorr_slider");
        k_scorr_slider->setMaximum(100);
        k_scorr_slider->setOrientation(Qt::Orientation::Horizontal);

        horizontalLayout_9->addWidget(k_scorr_slider);


        verticalLayout_7->addLayout(horizontalLayout_9);


        horizontalLayout_2->addLayout(verticalLayout_7);


        verticalLayout_2->addLayout(horizontalLayout_2);


        verticalLayout->addWidget(groupBox);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName("verticalLayout_3");

        verticalLayout->addLayout(verticalLayout_3);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 18));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        groupBox->setTitle(QCoreApplication::translate("MainWindow", "POSITION BASED FLUIDS", nullptr));
        start_button->setText(QCoreApplication::translate("MainWindow", "Start", nullptr));
        stop_button->setText(QCoreApplication::translate("MainWindow", "Stop", nullptr));
        restart_button->setText(QCoreApplication::translate("MainWindow", "Restart", nullptr));
        count_label->setText(QCoreApplication::translate("MainWindow", "Nombre de particules : 0", nullptr));
        btn_generate->setText(QCoreApplication::translate("MainWindow", "Generate", nullptr));
        amplitude_label->setText(QCoreApplication::translate("MainWindow", "Amplitude", nullptr));
        gravity_label->setText(QCoreApplication::translate("MainWindow", "Gravit\303\251", nullptr));
        coeffVorti_label->setText(QCoreApplication::translate("MainWindow", "Vorticit\303\251", nullptr));
        coeff_Visco_label->setText(QCoreApplication::translate("MainWindow", "Viscosit\303\251", nullptr));
        k_scorr_label->setText(QCoreApplication::translate("MainWindow", "k_scorr", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
