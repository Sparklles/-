/********************************************************************************
** Form generated from reading UI file 'EventDetailDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EVENTDETAILDIALOG_H
#define UI_EVENTDETAILDIALOG_H

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

class Ui_EventDetailDialogClass
{
public:
    QLineEdit *titleEdit;
    QLabel *label_2;
    QLabel *label;
    QTextEdit *descriptionEdit;
    QLabel *label_3;
    QPushButton *editButton;
    QPushButton *deleteButton;
    QPushButton *saveButton;
    QPushButton *cancelEditButton;
    QLabel *label_8;
    QLineEdit *locationEdit;
    QComboBox *categoryEdit;
    QLabel *label_9;
    QDateTimeEdit *eventTimeEdit;
    QLabel *label_10;

    void setupUi(QDialog *EventDetailDialogClass)
    {
        if (EventDetailDialogClass->objectName().isEmpty())
            EventDetailDialogClass->setObjectName(QString::fromUtf8("EventDetailDialogClass"));
        EventDetailDialogClass->resize(819, 578);
        titleEdit = new QLineEdit(EventDetailDialogClass);
        titleEdit->setObjectName(QString::fromUtf8("titleEdit"));
        titleEdit->setGeometry(QRect(130, 70, 166, 24));
        QFont font;
        font.setPointSize(11);
        titleEdit->setFont(font);
        label_2 = new QLabel(EventDetailDialogClass);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(60, 140, 31, 31));
        label_2->setFont(font);
        label = new QLabel(EventDetailDialogClass);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(91, 71, 30, 20));
        label->setFont(font);
        descriptionEdit = new QTextEdit(EventDetailDialogClass);
        descriptionEdit->setObjectName(QString::fromUtf8("descriptionEdit"));
        descriptionEdit->setGeometry(QRect(130, 130, 361, 111));
        descriptionEdit->setFont(font);
        label_3 = new QLabel(EventDetailDialogClass);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(90, 120, 31, 31));
        label_3->setFont(font);
        editButton = new QPushButton(EventDetailDialogClass);
        editButton->setObjectName(QString::fromUtf8("editButton"));
        editButton->setGeometry(QRect(660, 480, 61, 31));
        editButton->setFont(font);
        deleteButton = new QPushButton(EventDetailDialogClass);
        deleteButton->setObjectName(QString::fromUtf8("deleteButton"));
        deleteButton->setGeometry(QRect(650, 40, 61, 31));
        deleteButton->setFont(font);
        saveButton = new QPushButton(EventDetailDialogClass);
        saveButton->setObjectName(QString::fromUtf8("saveButton"));
        saveButton->setGeometry(QRect(660, 530, 71, 31));
        saveButton->setFont(font);
        cancelEditButton = new QPushButton(EventDetailDialogClass);
        cancelEditButton->setObjectName(QString::fromUtf8("cancelEditButton"));
        cancelEditButton->setGeometry(QRect(740, 530, 71, 31));
        cancelEditButton->setFont(font);
        label_8 = new QLabel(EventDetailDialogClass);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setGeometry(QRect(100, 350, 30, 20));
        label_8->setFont(font);
        locationEdit = new QLineEdit(EventDetailDialogClass);
        locationEdit->setObjectName(QString::fromUtf8("locationEdit"));
        locationEdit->setGeometry(QRect(136, 350, 181, 24));
        locationEdit->setFont(font);
        categoryEdit = new QComboBox(EventDetailDialogClass);
        categoryEdit->setObjectName(QString::fromUtf8("categoryEdit"));
        categoryEdit->setGeometry(QRect(136, 420, 181, 25));
        categoryEdit->setFont(font);
        label_9 = new QLabel(EventDetailDialogClass);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setGeometry(QRect(100, 420, 30, 20));
        label_9->setFont(font);
        eventTimeEdit = new QDateTimeEdit(EventDetailDialogClass);
        eventTimeEdit->setObjectName(QString::fromUtf8("eventTimeEdit"));
        eventTimeEdit->setGeometry(QRect(136, 280, 181, 24));
        eventTimeEdit->setFont(font);
        label_10 = new QLabel(EventDetailDialogClass);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setGeometry(QRect(100, 280, 30, 20));
        label_10->setFont(font);

        retranslateUi(EventDetailDialogClass);

        QMetaObject::connectSlotsByName(EventDetailDialogClass);
    } // setupUi

    void retranslateUi(QDialog *EventDetailDialogClass)
    {
        EventDetailDialogClass->setWindowTitle(QCoreApplication::translate("EventDetailDialogClass", "EventDetailDialog", nullptr));
        label_2->setText(QString());
        label->setText(QCoreApplication::translate("EventDetailDialogClass", "\346\240\207\351\242\230", nullptr));
        label_3->setText(QCoreApplication::translate("EventDetailDialogClass", "\345\206\205\345\256\271", nullptr));
        editButton->setText(QCoreApplication::translate("EventDetailDialogClass", "\347\274\226\350\276\221", nullptr));
        deleteButton->setText(QCoreApplication::translate("EventDetailDialogClass", "\345\210\240\351\231\244", nullptr));
        saveButton->setText(QCoreApplication::translate("EventDetailDialogClass", "\344\277\235\345\255\230", nullptr));
        cancelEditButton->setText(QCoreApplication::translate("EventDetailDialogClass", "\351\200\200\345\207\272\347\274\226\350\276\221", nullptr));
        label_8->setText(QCoreApplication::translate("EventDetailDialogClass", "\345\234\260\347\202\271", nullptr));
        locationEdit->setText(QString());
        label_9->setText(QCoreApplication::translate("EventDetailDialogClass", "\347\261\273\345\210\253", nullptr));
        label_10->setText(QCoreApplication::translate("EventDetailDialogClass", "\346\227\266\351\227\264", nullptr));
    } // retranslateUi

};

namespace Ui {
    class EventDetailDialogClass: public Ui_EventDetailDialogClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EVENTDETAILDIALOG_H
