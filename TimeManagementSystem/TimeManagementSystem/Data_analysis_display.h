#ifndef DATA_ANALYSIS_DISPLAY_H
#define DATA_ANALYSIS_DISPLAY_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class Data_analysis_display; }
QT_END_NAMESPACE

class Data_analysis_display : public QWidget
{
    Q_OBJECT

public:
    Data_analysis_display(QWidget *parent = nullptr);
    ~Data_analysis_display();

private:
    Ui::Data_analysis_display *ui;
};
#endif // DATA_ANALYSIS_DISPLAY_H
