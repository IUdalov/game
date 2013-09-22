#include "core_includes.h"
#include "main_window.h"

int main(int argc, char *argv[])
{
    qInstallMessageHandler(ReportSender);
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    
    return a.exec();
}
