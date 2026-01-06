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
    QPushButton *start_button;
    QPushButton *stop_button;
    QPushButton *restart_button;
    QLabel *count_label;
    QPushButton *btn_generate;
    QSpinBox *sb_particleCount;
    QHBoxLayout *horizontalLayout_3;
    QSlider *gravity_slider;
    QLabel *gravity_label;
    QSlider *stiffness_slider;
    QLabel *stiffness_label;
    QSlider *coeffSumR_slider;
    QLabel *coeffSumR_label;
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
        start_button = new QPushButton(groupBox);
        start_button->setObjectName("start_button");
        start_button->setEnabled(true);
        start_button->setIconSize(QSize(12, 12));

        horizontalLayout_2->addWidget(start_button);

        stop_button = new QPushButton(groupBox);
        stop_button->setObjectName("stop_button");

        horizontalLayout_2->addWidget(stop_button);

        restart_button = new QPushButton(groupBox);
        restart_button->setObjectName("restart_button");

        horizontalLayout_2->addWidget(restart_button);

        count_label = new QLabel(groupBox);
        count_label->setObjectName("count_label");

        horizontalLayout_2->addWidget(count_label);

        btn_generate = new QPushButton(groupBox);
        btn_generate->setObjectName("btn_generate");

        horizontalLayout_2->addWidget(btn_generate);

        sb_particleCount = new QSpinBox(groupBox);
        sb_particleCount->setObjectName("sb_particleCount");
        sb_particleCount->setMaximum(100000);

        horizontalLayout_2->addWidget(sb_particleCount);


        verticalLayout_2->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(10);
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        gravity_slider = new QSlider(groupBox);
        gravity_slider->setObjectName("gravity_slider");
        gravity_slider->setMaximum(1000);
        gravity_slider->setOrientation(Qt::Orientation::Horizontal);

        horizontalLayout_3->addWidget(gravity_slider);

        gravity_label = new QLabel(groupBox);
        gravity_label->setObjectName("gravity_label");

        horizontalLayout_3->addWidget(gravity_label);

        stiffness_slider = new QSlider(groupBox);
        stiffness_slider->setObjectName("stiffness_slider");
        stiffness_slider->setMaximum(100);
        stiffness_slider->setOrientation(Qt::Orientation::Horizontal);

        horizontalLayout_3->addWidget(stiffness_slider);

        stiffness_label = new QLabel(groupBox);
        stiffness_label->setObjectName("stiffness_label");

        horizontalLayout_3->addWidget(stiffness_label);

        coeffSumR_slider = new QSlider(groupBox);
        coeffSumR_slider->setObjectName("coeffSumR_slider");
        coeffSumR_slider->setMaximum(100);
        coeffSumR_slider->setOrientation(Qt::Orientation::Horizontal);

        horizontalLayout_3->addWidget(coeffSumR_slider);

        coeffSumR_label = new QLabel(groupBox);
        coeffSumR_label->setObjectName("coeffSumR_label");

        horizontalLayout_3->addWidget(coeffSumR_label);

        horizontalLayout_3->setStretch(0, 1);
        horizontalLayout_3->setStretch(1, 1);
        horizontalLayout_3->setStretch(2, 1);
        horizontalLayout_3->setStretch(3, 1);
        horizontalLayout_3->setStretch(4, 1);
        horizontalLayout_3->setStretch(5, 1);

        verticalLayout_2->addLayout(horizontalLayout_3);


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
        groupBox->setTitle(QCoreApplication::translate("MainWindow", "GroupBox", nullptr));
        start_button->setText(QCoreApplication::translate("MainWindow", "Start", nullptr));
        stop_button->setText(QCoreApplication::translate("MainWindow", "Stop", nullptr));
        restart_button->setText(QCoreApplication::translate("MainWindow", "Restart", nullptr));
        count_label->setText(QCoreApplication::translate("MainWindow", "Nombre de particules : 0", nullptr));
        btn_generate->setText(QCoreApplication::translate("MainWindow", "Generate", nullptr));
        gravity_label->setText(QCoreApplication::translate("MainWindow", "Gravity", nullptr));
        stiffness_label->setText(QCoreApplication::translate("MainWindow", "Raideur : 0", nullptr));
        coeffSumR_label->setText(QCoreApplication::translate("MainWindow", "Coefficient multiplicateur : 0", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
