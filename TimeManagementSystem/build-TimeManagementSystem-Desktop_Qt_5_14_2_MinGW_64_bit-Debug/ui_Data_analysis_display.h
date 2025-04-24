/********************************************************************************
** Form generated from reading UI file 'Data_analysis_display.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DATA_ANALYSIS_DISPLAY_H
#define UI_DATA_ANALYSIS_DISPLAY_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Data_analysis_display
{
public:

    void setupUi(QWidget *Data_analysis_display)
    {
        if (Data_analysis_display->objectName().isEmpty())
            Data_analysis_display->setObjectName(QString::fromUtf8("Data_analysis_display"));
        Data_analysis_display->resize(800, 600);

        retranslateUi(Data_analysis_display);

        QMetaObject::connectSlotsByName(Data_analysis_display);
    } // setupUi

    void retranslateUi(QWidget *Data_analysis_display)
    {
        Data_analysis_display->setWindowTitle(QCoreApplication::translate("Data_analysis_display", "Data_analysis_display", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Data_analysis_display: public Ui_Data_analysis_display {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DATA_ANALYSIS_DISPLAY_H
