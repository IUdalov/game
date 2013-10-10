#include "menu.h"

Menu menu;

Menu::Menu() : Model_Objects(STO_MENU, 0) {
}
Menu::~Menu(){
}

void Menu::EventsHandler(unsigned int mess, void*) {
    switch(mess){
    case ME_CREATE:
    {
        // создаём сетку
        ObjManager.ReBuildGrid(Root.GetScreenWidth() / 50 + 1, Root.GetScreenHeight() / 50 + 1, 50, 50, 0);
        Root.NumLevelDraw = DRAW_LEVELS;

//        CreateMenu();
        GameParam* gameparam;

        gameparam = (GameParam*)Root.PutEventToQueue(sizeof(GameParam), SE_STARTGAME, STO_CHEKERS);
        gameparam->FieldWidth = gameparam->FieldHeight = 8;
        gameparam->big_num = 4;
        gameparam->midle_num = 4;
        gameparam->small_num = 4;

    }
        break;
    case ME_MOUSECLICK:
        RemoveStartMenu();

        break;
    default:
        ;
    }
    return;
}

void Menu::CreateMenu() {
    IDn id;
    CObj obj;

    this->CreateSimpleObj(&obj);
    obj.BMP = ID_BMP_MENU_PLAY;
    obj.image = 0;
    obj.SetRectByImage();
    obj.LevelOfDraw = DRAW_MENU;
    obj.x = Root.GetScreenWidth() / 2;
    obj.y = Root.GetScreenHeight() / 2;
    ObjManager.CreateObj(obj, id);
    ObjManager.AddToGrid(id, false);

    return;
}

void Menu::RemoveStartMenu() {

    return;
}
