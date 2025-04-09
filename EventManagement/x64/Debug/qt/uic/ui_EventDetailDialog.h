/********************************************************************************
** Form generated from reading UI file 'EventDetailDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.5.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EVENTDETAILDIALOG_H
#define UI_EVENTDETAILDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDateTimeEdit>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>

QT_BEGIN_NAMESPACE

class Ui_EventDetailDialogClass
{
public:
    QLineEdit *titleEdit;
    QDateTimeEdit *endTimeEdit;
    QLabel *label_2;
    QDateTimeEdit *reminderTime;
    QLabel *label_4;
    QLabel *label_7;
    QLabel *label_5;
    QLabel *label;
    QTextEdit *descriptionEdit;
    QLabel *label_6;
    QLineEdit *locationEdit;
    QDateTimeEdit *startTimeEdit;
    QLabel *label_3;
    QPushButton *editButton;
    QPushButton *deleteButton;
    QPushButton *saveButton;
    QPushButton *cancelEditButton;

    void setupUi(QDialog *EventDetailDialogClass)
    {
        if (EventDetailDialogClass->objectName().isEmpty())
            EventDetailDialogClass->setObjectName("EventDetailDialogClass");
        EventDetailDialogClass->resize(819, 578);
        titleEdit = new QLineEdit(EventDetailDialogClass);
        titleEdit->setObjectName("titleEdit");
        titleEdit->setGeometry(QRect(140, 70, 191, 31));
        QFont font;
        font.setPointSize(11);
        titleEdit->setFont(font);
        endTimeEdit = new QDateTimeEdit(EventDetailDialogClass);
        endTimeEdit->setObjectName("endTimeEdit");
        endTimeEdit->setGeometry(QRect(140, 330, 194, 31));
        endTimeEdit->setFont(font);
        label_2 = new QLabel(EventDetailDialogClass);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(60, 140, 31, 31));
        label_2->setFont(font);
        reminderTime = new QDateTimeEdit(EventDetailDialogClass);
        reminderTime->setObjectName("reminderTime");
        reminderTime->setGeometry(QRect(140, 390, 194, 31));
        reminderTime->setFont(font);
        label_4 = new QLabel(EventDetailDialogClass);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(100, 270, 31, 31));
        label_4->setFont(font);
        label_7 = new QLabel(EventDetailDialogClass);
        label_7->setObjectName("label_7");
        label_7->setGeometry(QRect(100, 440, 31, 31));
        label_7->setFont(font);
        label_5 = new QLabel(EventDetailDialogClass);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(100, 330, 31, 31));
        label_5->setFont(font);
        label = new QLabel(EventDetailDialogClass);
        label->setObjectName("label");
        label->setGeometry(QRect(90, 70, 31, 31));
        label->setFont(font);
        descriptionEdit = new QTextEdit(EventDetailDialogClass);
        descriptionEdit->setObjectName("descriptionEdit");
        descriptionEdit->setGeometry(QRect(140, 130, 361, 111));
        descriptionEdit->setFont(font);
        label_6 = new QLabel(EventDetailDialogClass);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(100, 390, 31, 31));
        label_6->setFont(font);
        locationEdit = new QLineEdit(EventDetailDialogClass);
        locationEdit->setObjectName("locationEdit");
        locationEdit->setGeometry(QRect(140, 440, 191, 31));
        locationEdit->setFont(font);
        startTimeEdit = new QDateTimeEdit(EventDetailDialogClass);
        startTimeEdit->setObjectName("startTimeEdit");
        startTimeEdit->setGeometry(QRect(140, 270, 194, 31));
        startTimeEdit->setFont(font);
        label_3 = new QLabel(EventDetailDialogClass);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(90, 130, 31, 31));
        label_3->setFont(font);
        editButton = new QPushButton(EventDetailDialogClass);
        editButton->setObjectName("editButton");
        editButton->setGeometry(QRect(660, 480, 61, 31));
        editButton->setFont(font);
        deleteButton = new QPushButton(EventDetailDialogClass);
        deleteButton->setObjectName("deleteButton");
        deleteButton->setGeometry(QRect(650, 40, 61, 31));
        deleteButton->setFont(font);
        saveButton = new QPushButton(EventDetailDialogClass);
        saveButton->setObjectName("saveButton");
        saveButton->setGeometry(QRect(660, 530, 71, 31));
        saveButton->setFont(font);
        cancelEditButton = new QPushButton(EventDetailDialogClass);
        cancelEditButton->setObjectName("cancelEditButton");
        cancelEditButton->setGeometry(QRect(740, 530, 71, 31));
        cancelEditButton->setFont(font);

        retranslateUi(EventDetailDialogClass);

        QMetaObject::connectSlotsByName(EventDetailDialogClass);
    } // setupUi

    void retranslateUi(QDialog *EventDetailDialogClass)
    {
        EventDetailDialogClass->setWindowTitle(QCoreApplication::translate("EventDetailDialogClass", "EventDetailDialog", nullptr));
        label_2->setText(QString());
        label_4->setText(QCoreApplication::translate("EventDetailDialogClass", "\345\274\200\345\247\213", nullptr));
        label_7->setText(QCoreApplication::translate("EventDetailDialogClass", "\345\234\260\347\202\271", nullptr));
        label_5->setText(QCoreApplication::translate("EventDetailDialogClass", "\347\273\223\346\235\237", nullptr));
        label->setText(QCoreApplication::translate("EventDetailDialogClass", "\346\240\207\351\242\230", nullptr));
        label_6->setText(QCoreApplication::translate("EventDetailDialogClass", "\346\217\220\351\206\222", nullptr));
        locationEdit->setText(QString());
        label_3->setText(QCoreApplication::translate("EventDetailDialogClass", "\345\206\205\345\256\271", nullptr));
        editButton->setText(QCoreApplication::translate("EventDetailDialogClass", "\347\274\226\350\276\221", nullptr));
        deleteButton->setText(QCoreApplication::translate("EventDetailDialogClass", "\345\210\240\351\231\244", nullptr));
        saveButton->setText(QCoreApplication::translate("EventDetailDialogClass", "\344\277\235\345\255\230", nullptr));
        cancelEditButton->setText(QCoreApplication::translate("EventDetailDialogClass", "\351\200\200\345\207\272\347\274\226\350\276\221", nullptr));
    } // retranslateUi

};

namespace Ui {
    class EventDetailDialogClass: public Ui_EventDetailDialogClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EVENTDETAILDIALOG_H
