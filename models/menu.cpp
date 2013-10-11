#include "menu.h"

Menu menu;

Menu::Menu() : Model_Objects(STO_MENU, 0) {
    main_menu.reserve(ID_BMP_EXIT - ID_BMP_MENU_PLAY + 1);
    isCreated = false;
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

        //CreateMenu();
    }
        break; //// WARNING!!!
    case ME_MOUSECLICK:
    {
        if (!isCreated) {
        isCreated = true;
        // RemoveStartMenu();

        GameParam* gameparam;
        gameparam = (GameParam*)Root.PutEventToQueue(sizeof(GameParam), SE_STARTGAME, STO_CHEKERS);
        gameparam->FieldWidth = gameparam->FieldHeight = 8;
        gameparam->big_num = 4;
        gameparam->midle_num = 4;
        gameparam->small_num = 4;
        }
    }
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

    for (size_t i = ID_BMP_MENU_PLAY; i <= ID_BMP_EXIT; i++ ) {
        obj.BMP = ID_BMP_MENU_PLAY;
        obj.x = Root.GetScreenWidth() / 2;
        obj.y = Root.GetScreenHeight() * (i - ID_BMP_MENU_PLAY + 1) / 5;
        ObjManager.CreateObj(obj, id);
        ObjManager.AddToGrid(id, false);
        main_menu.push_back(id);
    }

    return;
}

void Menu::RemoveStartMenu() {
    for(size_t i  = 0; i < main_menu.size(); i++) {
        ObjManager.DeleteFromGrid(main_menu[i]);
    }
    return;
}
