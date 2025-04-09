/********************************************************************************
** Form generated from reading UI file 'EventDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.5.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EVENTDIALOG_H
#define UI_EVENTDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDateTimeEdit>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>

QT_BEGIN_NAMESPACE

class Ui_EventDialogClass
{
public:
    QLineEdit *titleEdit;
    QLabel *label;
    QLineEdit *locationEdit;
    QLabel *label_2;
    QLabel *label_3;
    QTextEdit *descriptionEdit;
    QLabel *label_4;
    QDateTimeEdit *startTimeEdit;
    QLabel *label_5;
    QDateTimeEdit *endTimeEdit;
    QDateTimeEdit *reminderTime;
    QLabel *label_6;
    QLabel *label_7;
    QPushButton *cancelButton;
    QPushButton *okButton;

    void setupUi(QDialog *EventDialogClass)
    {
        if (EventDialogClass->objectName().isEmpty())
            EventDialogClass->setObjectName("EventDialogClass");
        EventDialogClass->resize(830, 483);
        titleEdit = new QLineEdit(EventDialogClass);
        titleEdit->setObjectName("titleEdit");
        titleEdit->setGeometry(QRect(170, 40, 191, 21));
        QFont font;
        font.setPointSize(11);
        titleEdit->setFont(font);
        label = new QLabel(EventDialogClass);
        label->setObjectName("label");
        label->setGeometry(QRect(120, 30, 31, 31));
        label->setFont(font);
        locationEdit = new QLineEdit(EventDialogClass);
        locationEdit->setObjectName("locationEdit");
        locationEdit->setGeometry(QRect(170, 400, 191, 31));
        locationEdit->setFont(font);
        label_2 = new QLabel(EventDialogClass);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(90, 100, 31, 31));
        label_2->setFont(font);
        label_3 = new QLabel(EventDialogClass);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(120, 90, 31, 31));
        label_3->setFont(font);
        descriptionEdit = new QTextEdit(EventDialogClass);
        descriptionEdit->setObjectName("descriptionEdit");
        descriptionEdit->setGeometry(QRect(170, 90, 361, 111));
        descriptionEdit->setFont(font);
        label_4 = new QLabel(EventDialogClass);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(130, 230, 31, 31));
        label_4->setFont(font);
        startTimeEdit = new QDateTimeEdit(EventDialogClass);
        startTimeEdit->setObjectName("startTimeEdit");
        startTimeEdit->setGeometry(QRect(170, 230, 194, 31));
        startTimeEdit->setFont(font);
        label_5 = new QLabel(EventDialogClass);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(130, 290, 31, 31));
        label_5->setFont(font);
        endTimeEdit = new QDateTimeEdit(EventDialogClass);
        endTimeEdit->setObjectName("endTimeEdit");
        endTimeEdit->setGeometry(QRect(170, 290, 194, 31));
        endTimeEdit->setFont(font);
        reminderTime = new QDateTimeEdit(EventDialogClass);
        reminderTime->setObjectName("reminderTime");
        reminderTime->setGeometry(QRect(170, 350, 194, 31));
        reminderTime->setFont(font);
        label_6 = new QLabel(EventDialogClass);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(130, 350, 31, 31));
        label_6->setFont(font);
        label_7 = new QLabel(EventDialogClass);
        label_7->setObjectName("label_7");
        label_7->setGeometry(QRect(130, 400, 31, 31));
        label_7->setFont(font);
        cancelButton = new QPushButton(EventDialogClass);
        cancelButton->setObjectName("cancelButton");
        cancelButton->setGeometry(QRect(720, 420, 61, 31));
        cancelButton->setFont(font);
        okButton = new QPushButton(EventDialogClass);
        okButton->setObjectName("okButton");
        okButton->setGeometry(QRect(630, 420, 61, 31));
        okButton->setFont(font);

        retranslateUi(EventDialogClass);

        QMetaObject::connectSlotsByName(EventDialogClass);
    } // setupUi

    void retranslateUi(QDialog *EventDialogClass)
    {
        EventDialogClass->setWindowTitle(QCoreApplication::translate("EventDialogClass", "EventDialog", nullptr));
        label->setText(QCoreApplication::translate("EventDialogClass", "\346\240\207\351\242\230", nullptr));
        locationEdit->setText(QString());
        label_2->setText(QString());
        label_3->setText(QCoreApplication::translate("EventDialogClass", "\345\206\205\345\256\271", nullptr));
        label_4->setText(QCoreApplication::translate("EventDialogClass", "\345\274\200\345\247\213", nullptr));
        label_5->setText(QCoreApplication::translate("EventDialogClass", "\347\273\223\346\235\237", nullptr));
        label_6->setText(QCoreApplication::translate("EventDialogClass", "\346\217\220\351\206\222", nullptr));
        label_7->setText(QCoreApplication::translate("EventDialogClass", "\345\234\260\347\202\271", nullptr));
        cancelButton->setText(QCoreApplication::translate("EventDialogClass", "\345\217\226\346\266\210", nullptr));
        okButton->setText(QCoreApplication::translate("EventDialogClass", "\347\241\256\345\256\232", nullptr));
    } // retranslateUi

};

namespace Ui {
    class EventDialogClass: public Ui_EventDialogClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EVENTDIALOG_H
