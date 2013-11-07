#include "INDIan/core_includes.h"

#include "inits/declarations.h"
#include "models/checker_manager.h"
#include "models/field.h"
#include "models/menu.h"

int main(int argc, char *argv[])
{
    //qInstallMessageHandler(ReportSender);
    CheckerManager checkerManager;
    Field          field;
    Menu           menu;

    Root::AccessModel((Model*)&checkerManager);
    Root::AccessModel((Model*)&field);
    Root::AccessModel((Model*)&menu);

    Resources::Init();
    ObjManager::Init();

    Resources::UserTilesLoader = initImages;

    QApplication a(argc, argv);
    GLWindow window;
    window.Run();
    
    return a.exec();
}
