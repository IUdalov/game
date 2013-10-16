#include "menu.h"

void Menu::InitMenuItems() {

    IDn id;
    CObj obj;
    this->CreateSimpleObj(&obj);
    obj.image = 0;
    obj.LevelOfDraw = DRAW_MENU;

    obj.x = Root.GetScreenWidth() / 2;
    obj.y = Root.GetScreenHeight() / 5;
    obj.BMP = ID_BMP_MENU_PLAY;
    obj.SetRectByImage();
    ObjManager.CreateObj(obj, id);
    menuItems[ID_BMP_MENU_PLAY] = id;

    obj.x = Root.GetScreenWidth() / 2;
    obj.y = Root.GetScreenHeight() * 2 / 5;
    obj.BMP = ID_BMP_RULES;
    obj.SetRectByImage();
    ObjManager.CreateObj(obj, id);
    menuItems[ID_BMP_RULES] = id;

    obj.x = Root.GetScreenWidth() / 2;
    obj.y = Root.GetScreenHeight() * 3 / 5;
    obj.BMP = ID_BMP_OPTIONS;
    obj.SetRectByImage();
    ObjManager.CreateObj(obj, id);
    menuItems[ID_BMP_OPTIONS] = id;

    obj.x = Root.GetScreenWidth() / 2;
    obj.y = Root.GetScreenHeight() * 4 / 5;
    obj.BMP = ID_BMP_EXIT;
    obj.SetRectByImage();
    ObjManager.CreateObj(obj, id);
    menuItems[ID_BMP_EXIT] = id;

    obj.x = Root.GetScreenWidth() / 9;
    obj.y = Root.GetScreenHeight() * 7 / 8;
    obj.BMP = ID_BMP_BACK;
    obj.SetRectByImage();
    ObjManager.CreateObj(obj, id);
    menuItems[ID_BMP_BACK] = id;

    obj.x = Root.GetScreenWidth() * 8 / 9;
    obj.y = Root.GetScreenHeight() * 7 / 8;
    obj.BMP = ID_BMP_PLAY;
    obj.SetRectByImage();
    ObjManager.CreateObj(obj, id);
    menuItems[ID_BMP_PLAY] = id;

    obj.x = Root.GetScreenWidth() / 8;
    obj.y = Root.GetScreenHeight() / 8;
    obj.BMP = ID_BMP_PAUSE;
    obj.SetRectByImage();
    ObjManager.CreateObj(obj, id);
    menuItems[ID_BMP_PAUSE] = id;

    obj.x = Root.GetScreenWidth() / 9;
    obj.y = Root.GetScreenHeight() / 8;
    obj.BMP = ID_BMP_RESTART;
    obj.SetRectByImage();
    ObjManager.CreateObj(obj, id);
    menuItems[ID_BMP_RESTART] = id;
    return;
}


void Menu::ShowStartMenu() {
    ShowMenuItem(ID_BMP_MENU_PLAY);
    ShowMenuItem(ID_BMP_RULES);
    ShowMenuItem(ID_BMP_OPTIONS);
    ShowMenuItem(ID_BMP_EXIT);
    return;
}

void Menu::HideStartMenu() {
    HideMenuItem(ID_BMP_MENU_PLAY);
    HideMenuItem(ID_BMP_RULES);
    HideMenuItem(ID_BMP_OPTIONS);
    HideMenuItem(ID_BMP_EXIT);
    return;
}

void Menu::ShowPositionMenu() {
    ShowMenuItem(ID_BMP_PLAY);
    ShowMenuItem(ID_BMP_BACK);
    return;
}

void Menu::HidePositionMenu() {
    HideMenuItem(ID_BMP_PLAY);
    HideMenuItem(ID_BMP_BACK);
    return;
}

void Menu::ShowOptionMenu() {
    ShowMenuItem(ID_BMP_BACK);
    return;
}

void Menu::HideOptionMenu() {
    HideMenuItem(ID_BMP_BACK);
    return;
}

void Menu::ShowRulesMenu() {
    ShowMenuItem(ID_BMP_BACK);
    return;
}

void Menu::HideRulesMenu() {
    HideMenuItem(ID_BMP_BACK);
    return;
}

void Menu::ShowPauseMenu() {
    ShowMenuItem(ID_BMP_BACK);
    ShowMenuItem(ID_BMP_PLAY);
    ShowMenuItem(ID_BMP_RESTART);
    return;
}

void Menu::HidePauseMenu() {
    HideMenuItem(ID_BMP_BACK);
    HideMenuItem(ID_BMP_PLAY);
    HideMenuItem(ID_BMP_RESTART);
    return;
}

void Menu::ShowGameMenu() {
    ShowMenuItem(ID_BMP_PAUSE);
    return;
}

void Menu::HideGameMenu() {
    HideMenuItem(ID_BMP_PAUSE);
    return;
}
