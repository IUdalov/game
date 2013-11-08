#ifndef MENU_H
#define MENU_H

#include "../inits/declarations.h"
#include "../INDIan/core_includes.h"
#include "../physics/physics.h"

using namespace INDIan;

typedef map<int, IDn> MenuItems;

class Menu : public Model {
    enum {
        Start = 0,
        PositionSingle,
        PositionMulti,
        Option,
        Rules,
        Pause,
        GameActive,
        GameSuspend
    };
public:
    Menu();
    virtual ~Menu();
    virtual void EventsHandler(int mess, void*);

private:
    MenuItems menuItems;
    int currMenu;

private:
    void InitMenuItems();
    void ShowMenuItem(int);
    void HideMenuItem(int);

    void ShowStartMenu();
    void HideStartMenu();
    void ShowPositionSingleMenu();
    void HidePositionSingleMenu();
    void ShowPositionMultiMenu();
    void HidePositionMultiMenu();
    void ShowOptionMenu();
    void HideOptionMenu();
    void ShowRulesMenu();
    void HideRulesMenu();
    void ShowPauseMenu();
    void HidePauseMenu();
    void ShowGameMenu();
    void HideGameMenu();

private:
    void MouseClick(IDn, SMouse);
};

#endif // MENU_H
