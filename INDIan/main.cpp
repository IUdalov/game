//#include <QDebug>
#include "core_includes.h"
#include "MainWindow.h"

// пока просто для тестов
#include "../physics/physics.h"

int main(int argc, char *argv[])
{
    //qDebug() << "Date:" << QDate::currentDate()<< "Start project!";

    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    
    return a.exec();
}
