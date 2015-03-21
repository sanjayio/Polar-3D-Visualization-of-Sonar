/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created: Wed Jun 25 10:20:17 2014
**      by: Qt User Interface Compiler version 4.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QMainWindow>
#include <QtGui/QSlider>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>
#include "glwidget.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout;
    GLWidget *widget;
    QSlider *xSlider;
    QSlider *ySlider;
    QSlider *zSlider;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(471, 428);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        horizontalLayout = new QHBoxLayout(centralWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        widget = new GLWidget(centralWidget);
        widget->setObjectName(QString::fromUtf8("widget"));

        verticalLayout->addWidget(widget);

        xSlider = new QSlider(centralWidget);
        xSlider->setObjectName(QString::fromUtf8("xSlider"));
        xSlider->setMaximum(360);
        xSlider->setSingleStep(16);
        xSlider->setPageStep(15);
        xSlider->setOrientation(Qt::Horizontal);
        xSlider->setTickPosition(QSlider::TicksAbove);
        xSlider->setTickInterval(15);

        verticalLayout->addWidget(xSlider);

        ySlider = new QSlider(centralWidget);
        ySlider->setObjectName(QString::fromUtf8("ySlider"));
        ySlider->setMaximum(360);
        ySlider->setSingleStep(16);
        ySlider->setPageStep(15);
        ySlider->setOrientation(Qt::Horizontal);
        ySlider->setTickPosition(QSlider::TicksAbove);
        ySlider->setTickInterval(15);

        verticalLayout->addWidget(ySlider);

        zSlider = new QSlider(centralWidget);
        zSlider->setObjectName(QString::fromUtf8("zSlider"));
        zSlider->setMaximum(360);
        zSlider->setSingleStep(16);
        zSlider->setPageStep(15);
        zSlider->setOrientation(Qt::Horizontal);
        zSlider->setTickPosition(QSlider::TicksAbove);
        zSlider->setTickInterval(15);

        verticalLayout->addWidget(zSlider);


        horizontalLayout->addLayout(verticalLayout);

        MainWindow->setCentralWidget(centralWidget);

        retranslateUi(MainWindow);
        QObject::connect(xSlider, SIGNAL(valueChanged(int)), widget, SLOT(setXRotation(int)));
        QObject::connect(ySlider, SIGNAL(valueChanged(int)), widget, SLOT(setYRotation(int)));
        QObject::connect(zSlider, SIGNAL(valueChanged(int)), widget, SLOT(setZRotation(int)));

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
