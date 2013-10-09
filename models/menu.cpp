#include "menu.h"

//Menu menu;

Menu::Menu() : Model_Objects(STO_MENU, 0) {
}
Menu::~Menu(){
}

void Menu::EventsHandler(unsigned int mess, void *data) {
    switch(mess){
    case ME_CREATE:
    {
        /*IDn id;
        CObj obj;
        this->CreateSimpleObj(&obj);
        obj.BMP = ID_BMP_MENU_PLAY;
        obj.image = 0;
        obj.SetRectByImage();
        obj.LevelOfDraw = 0;
        obj.x = 100;
        obj.y = 100;
        ObjManager.CreateObj(obj, id);
        ObjManager.AddToGrid(id, true);*/
    }
        break;
    case ME_DRAW:

        break;
    default:
        ;
    }
}
