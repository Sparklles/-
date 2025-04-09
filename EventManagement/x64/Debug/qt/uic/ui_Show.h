/********************************************************************************
** Form generated from reading UI file 'Show.ui'
**
** Created by: Qt User Interface Compiler version 6.5.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SHOW_H
#define UI_SHOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCalendarWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ShowClass
{
public:
    QWidget *centralWidget;
    QCalendarWidget *calendarWidget;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *ShowClass)
    {
        if (ShowClass->objectName().isEmpty())
            ShowClass->setObjectName("ShowClass");
        ShowClass->resize(797, 517);
        centralWidget = new QWidget(ShowClass);
        centralWidget->setObjectName("centralWidget");
        calendarWidget = new QCalendarWidget(centralWidget);
        calendarWidget->setObjectName("calendarWidget");
        calendarWidget->setGeometry(QRect(150, 80, 391, 211));
        ShowClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(ShowClass);
        menuBar->setObjectName("menuBar");
        menuBar->setGeometry(QRect(0, 0, 797, 22));
        ShowClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(ShowClass);
        mainToolBar->setObjectName("mainToolBar");
        ShowClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(ShowClass);
        statusBar->setObjectName("statusBar");
        ShowClass->setStatusBar(statusBar);

        retranslateUi(ShowClass);

        QMetaObject::connectSlotsByName(ShowClass);
    } // setupUi

    void retranslateUi(QMainWindow *ShowClass)
    {
        ShowClass->setWindowTitle(QCoreApplication::translate("ShowClass", "Show", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ShowClass: public Ui_ShowClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SHOW_H
