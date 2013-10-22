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

enum {
    Start = 0,
    Position,
    Option,
    Rules,
    Pause,
    GameActive,
    GameSuspend
};
typedef map<int, IDn> MenuItems;

class Menu : public Model_Objects {
public:
    Menu();
    virtual ~Menu();
    virtual void EventsHandler(unsigned int mess, void*);

private:
    MenuItems menuItems;
    int currMenu;

private:
    void InitMenuItems();
    void ShowMenuItem(int);
    void HideMenuItem(int);

    void ShowStartMenu();
    void HideStartMenu();
    void ShowPositionMenu();
    void HidePositionMenu();
    void ShowOptionMenu();
    void HideOptionMenu();
    void ShowRulesMenu();
    void HideRulesMenu();
    void ShowPauseMenu();
    void HidePauseMenu();
    void ShowGameMenu();
    void HideGameMenu();

private:
    void MouseClick(IDn, sMouse);
};

#endif // MENU_H
