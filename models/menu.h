#ifndef MENU_H
#define MENU_H

#include "../inits/declarations.h"
#include "../INDIan/core_includes.h"
#include "../physics/physics.h"

extern System_ROOT Root;
extern int ScreenWidth;
extern int ScreenHeight;
extern cResources Resources;
extern Obj_Manager ObjManager;

class Menu : public Model_Objects {
public:
    Menu();
    virtual ~Menu();

    virtual void EventsHandler(unsigned int mess, void *data);

};

#endif // MENU_H
