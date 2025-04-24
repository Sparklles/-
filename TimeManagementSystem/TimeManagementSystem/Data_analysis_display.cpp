#include "Data_analysis_display.h"
#include "ui_Data_analysis_display.h"

Data_analysis_display::Data_analysis_display(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Data_analysis_display)
{
    ui->setupUi(this);
}

Data_analysis_display::~Data_analysis_display()
{
    delete ui;
}

