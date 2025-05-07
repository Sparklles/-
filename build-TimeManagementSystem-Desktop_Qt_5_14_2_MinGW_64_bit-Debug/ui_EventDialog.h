/********************************************************************************
** Form generated from reading UI file 'EventDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EVENTDIALOG_H
#define UI_EVENTDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
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
    QLabel *label_2;
    QLabel *label_3;
    QTextEdit *descriptionEdit;
    QPushButton *cancelButton;
    QPushButton *okButton;
    QLabel *label_8;
    QComboBox *categoryComboBox;
    QLineEdit *titleEdit;
    QLabel *label;
    QLineEdit *locationEdit;
    QLabel *label_7;
    QLabel *label_4;
    QDateTimeEdit *eventTimeEdit;

    void setupUi(QDialog *EventDialogClass)
    {
        if (EventDialogClass->objectName().isEmpty())
            EventDialogClass->setObjectName(QString::fromUtf8("EventDialogClass"));
        EventDialogClass->resize(830, 483);
        label_2 = new QLabel(EventDialogClass);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(90, 100, 31, 31));
        QFont font;
        font.setPointSize(11);
        label_2->setFont(font);
        label_3 = new QLabel(EventDialogClass);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(130, 90, 31, 21));
        label_3->setFont(font);
        descriptionEdit = new QTextEdit(EventDialogClass);
        descriptionEdit->setObjectName(QString::fromUtf8("descriptionEdit"));
        descriptionEdit->setGeometry(QRect(170, 90, 361, 111));
        descriptionEdit->setFont(font);
        cancelButton = new QPushButton(EventDialogClass);
        cancelButton->setObjectName(QString::fromUtf8("cancelButton"));
        cancelButton->setGeometry(QRect(720, 420, 61, 31));
        cancelButton->setFont(font);
        okButton = new QPushButton(EventDialogClass);
        okButton->setObjectName(QString::fromUtf8("okButton"));
        okButton->setGeometry(QRect(630, 420, 61, 31));
        okButton->setFont(font);
        label_8 = new QLabel(EventDialogClass);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setGeometry(QRect(131, 371, 30, 20));
        label_8->setFont(font);
        categoryComboBox = new QComboBox(EventDialogClass);
        categoryComboBox->setObjectName(QString::fromUtf8("categoryComboBox"));
        categoryComboBox->setGeometry(QRect(167, 371, 181, 25));
        categoryComboBox->setFont(font);
        titleEdit = new QLineEdit(EventDialogClass);
        titleEdit->setObjectName(QString::fromUtf8("titleEdit"));
        titleEdit->setGeometry(QRect(170, 30, 166, 24));
        titleEdit->setFont(font);
        label = new QLabel(EventDialogClass);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(130, 30, 30, 20));
        label->setFont(font);
        locationEdit = new QLineEdit(EventDialogClass);
        locationEdit->setObjectName(QString::fromUtf8("locationEdit"));
        locationEdit->setGeometry(QRect(167, 301, 181, 24));
        locationEdit->setFont(font);
        label_7 = new QLabel(EventDialogClass);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setGeometry(QRect(131, 301, 30, 20));
        label_7->setFont(font);
        label_4 = new QLabel(EventDialogClass);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(131, 231, 30, 20));
        label_4->setFont(font);
        eventTimeEdit = new QDateTimeEdit(EventDialogClass);
        eventTimeEdit->setObjectName(QString::fromUtf8("eventTimeEdit"));
        eventTimeEdit->setGeometry(QRect(167, 231, 181, 24));
        eventTimeEdit->setFont(font);

        retranslateUi(EventDialogClass);

        QMetaObject::connectSlotsByName(EventDialogClass);
    } // setupUi

    void retranslateUi(QDialog *EventDialogClass)
    {
        EventDialogClass->setWindowTitle(QCoreApplication::translate("EventDialogClass", "EventDialog", nullptr));
        label_2->setText(QString());
        label_3->setText(QCoreApplication::translate("EventDialogClass", "\345\206\205\345\256\271", nullptr));
        cancelButton->setText(QCoreApplication::translate("EventDialogClass", "\345\217\226\346\266\210", nullptr));
        okButton->setText(QCoreApplication::translate("EventDialogClass", "\347\241\256\345\256\232", nullptr));
        label_8->setText(QCoreApplication::translate("EventDialogClass", "\347\261\273\345\210\253", nullptr));
        label->setText(QCoreApplication::translate("EventDialogClass", "\346\240\207\351\242\230", nullptr));
        locationEdit->setText(QString());
        label_7->setText(QCoreApplication::translate("EventDialogClass", "\345\234\260\347\202\271", nullptr));
        label_4->setText(QCoreApplication::translate("EventDialogClass", "\346\227\266\351\227\264", nullptr));
    } // retranslateUi

};

namespace Ui {
    class EventDialogClass: public Ui_EventDialogClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EVENTDIALOG_H
