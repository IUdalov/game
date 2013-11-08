#include "menu.h"

void Menu::InitMenuItems() {
    IDn id;
    Object obj;
    obj.subType = STO_MENU;
    obj.sizeOfSubStr = 0;
    obj.image = 0;
    obj.levelOfDraw = DRAW_MENU;
    obj.geo.type = GEO_BREP;

    obj.x = GLWindow::GetScreenWidth() / 2;
    obj.y = GLWindow::GetScreenHeight() / 6;
    obj.tileId = ID_BMP_MENU_SINGLE;
    obj.geo.preScaner = gps_for_menu_rect;
    obj.SetRectByImage();
    ObjManager::CreateObj(obj, id);
    menuItems[ID_BMP_MENU_SINGLE] = id;

    obj.x = GLWindow::GetScreenWidth() / 2;
    obj.y = GLWindow::GetScreenHeight() * 2 / 6;
    obj.tileId = ID_BMP_MENU_MULTI;
    obj.geo.preScaner = gps_for_menu_rect;
    obj.SetRectByImage();
    ObjManager::CreateObj(obj, id);
    menuItems[ID_BMP_MENU_MULTI] = id;

    obj.x = GLWindow::GetScreenWidth() / 2;
    obj.y = GLWindow::GetScreenHeight() * 3 / 6;
    obj.tileId = ID_BMP_RULES;
    obj.geo.preScaner = gps_for_menu_rect;
    obj.SetRectByImage();
    ObjManager::CreateObj(obj, id);
    menuItems[ID_BMP_RULES] = id;

    obj.x = GLWindow::GetScreenWidth() / 2;
    obj.y = GLWindow::GetScreenHeight() * 4 / 6;
    obj.tileId = ID_BMP_OPTIONS;
    obj.geo.preScaner = gps_for_menu_rect;
    obj.SetRectByImage();
    ObjManager::CreateObj(obj, id);
    menuItems[ID_BMP_OPTIONS] = id;

    obj.x = GLWindow::GetScreenWidth() / 2;
    obj.y = GLWindow::GetScreenHeight() * 5 / 6;
    obj.tileId = ID_BMP_EXIT;
    obj.geo.preScaner = gps_for_menu_rect;
    obj.SetRectByImage();
    ObjManager::CreateObj(obj, id);
    menuItems[ID_BMP_EXIT] = id;

    obj.x = Resources::GetTile(ID_BMP_BACK)->GetWidth() / 2;//GLWindow::GetScreenWidth() / 9;
    obj.y = GLWindow::GetScreenHeight() - Resources::GetTile(ID_BMP_BACK)->GetHeight() / 2;//* 7 / 8;
    obj.tileId = ID_BMP_BACK;
    obj.geo.preScaner = gps_for_menu_circle;
    obj.SetRectByImage();
    ObjManager::CreateObj(obj, id);
    menuItems[ID_BMP_BACK] = id;

    obj.x = GLWindow::GetScreenWidth() - Resources::GetTile(ID_BMP_PLAY)->GetWidth() / 2;//GLWindow::GetScreenWidth() * 8 / 9;
    obj.y = GLWindow::GetScreenHeight() - Resources::GetTile(ID_BMP_PLAY)->GetHeight() / 2;//GLWindow::GetScreenHeight() * 7 / 8;
    obj.tileId = ID_BMP_PLAY;
    obj.geo.preScaner = gps_for_menu_circle;
    obj.SetRectByImage();
    ObjManager::CreateObj(obj, id);
    menuItems[ID_BMP_PLAY] = id;

    obj.x = Resources::GetTile(ID_BMP_PAUSE)->GetWidth() / 2;//GLWindow::GetScreenWidth() / 8;
    obj.y = Resources::GetTile(ID_BMP_PAUSE)->GetHeight() / 2;//GLWindow::GetScreenHeight() / 8;
    obj.tileId = ID_BMP_PAUSE;
    obj.geo.preScaner = gps_for_menu_circle;
    obj.SetRectByImage();
    ObjManager::CreateObj(obj, id);
    menuItems[ID_BMP_PAUSE] = id;

    obj.x = Resources::GetTile(ID_BMP_RESTART)->GetWidth() / 2;//GLWindow::GetScreenWidth() / 9;
    obj.y = Resources::GetTile(ID_BMP_RESTART)->GetHeight() / 2;//GLWindow::GetScreenHeight() / 8;
    obj.tileId = ID_BMP_RESTART;
    obj.geo.preScaner = gps_for_menu_circle;
    obj.SetRectByImage();
    ObjManager::CreateObj(obj, id);
    menuItems[ID_BMP_RESTART] = id;
    return;
}


void Menu::ShowStartMenu() {
    ShowMenuItem(ID_BMP_MENU_SINGLE);
    ShowMenuItem(ID_BMP_MENU_MULTI);
    ShowMenuItem(ID_BMP_RULES);
    ShowMenuItem(ID_BMP_OPTIONS);
    ShowMenuItem(ID_BMP_EXIT);
    return;
}

void Menu::HideStartMenu() {
    HideMenuItem(ID_BMP_MENU_SINGLE);
    HideMenuItem(ID_BMP_MENU_MULTI);
    HideMenuItem(ID_BMP_RULES);
    HideMenuItem(ID_BMP_OPTIONS);
    HideMenuItem(ID_BMP_EXIT);
    return;
}

void Menu::ShowPositionSingleMenu() {
    ShowMenuItem(ID_BMP_PLAY);
    ShowMenuItem(ID_BMP_BACK);
    return;
}

void Menu::HidePositionSingleMenu() {
    HideMenuItem(ID_BMP_PLAY);
    HideMenuItem(ID_BMP_BACK);
    return;
}

void Menu::ShowPositionMultiMenu() {
    ShowMenuItem(ID_BMP_PLAY);
    ShowMenuItem(ID_BMP_BACK);
    return;
}

void Menu::HidePositionMultiMenu() {
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
