/********************************************************************************
** Form generated from reading UI file 'EventManager.ui'
**
** Created by: Qt User Interface Compiler version 6.5.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EVENTMANAGER_H
#define UI_EVENTMANAGER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCalendarWidget>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_EventManagerClass
{
public:
    QWidget *centralWidget;
    QCalendarWidget *calendarWidget;
    QPushButton *CreateButton;
    QListWidget *listWidget;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *EventManagerClass)
    {
        if (EventManagerClass->objectName().isEmpty())
            EventManagerClass->setObjectName("EventManagerClass");
        EventManagerClass->resize(1108, 660);
        centralWidget = new QWidget(EventManagerClass);
        centralWidget->setObjectName("centralWidget");
        calendarWidget = new QCalendarWidget(centralWidget);
        calendarWidget->setObjectName("calendarWidget");
        calendarWidget->setGeometry(QRect(80, 60, 641, 341));
        QFont font;
        font.setPointSize(11);
        calendarWidget->setFont(font);
        CreateButton = new QPushButton(centralWidget);
        CreateButton->setObjectName("CreateButton");
        CreateButton->setGeometry(QRect(990, 60, 91, 31));
        CreateButton->setFont(font);
        listWidget = new QListWidget(centralWidget);
        listWidget->setObjectName("listWidget");
        listWidget->setGeometry(QRect(90, 440, 641, 111));
        listWidget->setFont(font);
        EventManagerClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(EventManagerClass);
        menuBar->setObjectName("menuBar");
        menuBar->setGeometry(QRect(0, 0, 1108, 22));
        EventManagerClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(EventManagerClass);
        mainToolBar->setObjectName("mainToolBar");
        EventManagerClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(EventManagerClass);
        statusBar->setObjectName("statusBar");
        EventManagerClass->setStatusBar(statusBar);

        retranslateUi(EventManagerClass);

        QMetaObject::connectSlotsByName(EventManagerClass);
    } // setupUi

    void retranslateUi(QMainWindow *EventManagerClass)
    {
        EventManagerClass->setWindowTitle(QCoreApplication::translate("EventManagerClass", "EventManager", nullptr));
        CreateButton->setText(QCoreApplication::translate("EventManagerClass", "\345\210\233\345\273\272", nullptr));
    } // retranslateUi

};

namespace Ui {
    class EventManagerClass: public Ui_EventManagerClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EVENTMANAGER_H
