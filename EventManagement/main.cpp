#include "Show.h"
#include"EventManager.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    EventManager w;
    w.show();
    return a.exec();
}
