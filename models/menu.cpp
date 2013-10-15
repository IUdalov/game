#include "menu.h"

Menu menu;

Menu::Menu() : Model_Objects(STO_MENU, 0), currMenu(Start) {
}
Menu::~Menu(){
}

void Menu::EventsHandler(unsigned int mess, void*) {
    switch(mess){
    case ME_CREATE:
    {
        ObjManager.ReBuildGrid(Root.GetScreenWidth() / 50 + 1, Root.GetScreenHeight() / 50 + 1, 50, 50, 0);
        Root.NumLevelDraw = DRAW_LEVELS;

        InitMenuItems();
        ShowStartMenu();
        currMenu = Start;
    }
        break;
    case ME_MOUSECLICK:
    {

        MouseClick();

    }
        break;
    default:
        ;
    }
    return;
}

void Menu::ShowMenuItem(int item) {
     ObjManager.AddToGrid((*menuItems.find(item)).second, false);
     return;
}

void Menu::HideMenuItem(int item) {
    ObjManager.DeleteFromGrid((*menuItems.find(item)).second);
    return;
}

void Menu::MouseClick() {
    CObj obj;
    sMouse mouse = Root.GetMouseStatus();
    if(mouse.L == S_DOWN) {
        vector<IDn>* vObj = ObjManager.GetVObjByCrd(mouse.x, mouse.y);
        for(size_t i = 0; i < vObj->size(); i++) {
            ObjManager.GetObj((*vObj)[i], obj);
            switch (obj.BMP) {

            case ID_BMP_MENU_PLAY:
                HideStartMenu();
                currMenu = Position;
                ShowPositionMenu();
                break;

            case ID_BMP_RULES:
                HideStartMenu();
                currMenu = Rules;
                ShowRulesMenu();
                break;

            case ID_BMP_OPTIONS:
                HideStartMenu();
                currMenu = Option;
                ShowOptionMenu();
                break;

            case ID_BMP_EXIT:
                exit(0); // надо бы по нормальному выходить
                break;

            case ID_BMP_BACK:
                switch (currMenu) { // руки мне за это оторвать
                case Option:
                    HideOptionMenu();
                    break;
                case Rules:
                    HideRulesMenu();
                    break;
                case Position:
                    HidePositionMenu();
                    break;
                case GameSuspend:
                    HidePauseMenu();
                    Root.PutEventToQueue(SE_DELETEFIELD, STO_CHEKERS);
                    break;
                default:
                    ;
                }
                currMenu = Start;
                ShowStartMenu();
                break;

            case ID_BMP_PLAY:
            {
                if (currMenu == Position) {
                    HidePositionMenu();
                    currMenu = GameActive;
                    ShowGameMenu();
                    GameParam* gameparam;
                    gameparam = (GameParam*)Root.PutEventToQueue(sizeof(GameParam), SE_STARTGAME, STO_CHEKERS);
                    gameparam->FieldWidth = gameparam->FieldHeight = 8;
                    gameparam->big_num = 4;
                    gameparam->midle_num = 4;
                    gameparam->small_num = 4;
                }

                if (currMenu == GameSuspend) {
                    HidePauseMenu();
                    currMenu = GameActive;
                    ShowGameMenu();
                }
            }
                break;

            case ID_BMP_PAUSE:
                HideGameMenu();
                currMenu = GameSuspend;
                ShowPauseMenu();
                break;

            case ID_BMP_RESTART:
                HideGameMenu();;
                currMenu = GameActive;
                ShowGameMenu();
                Root.PutEventToQueue(0, SE_REPLAY, STO_CHEKERS);
                break;

            default:
                ;
            }
        }
       // delete
    }
    return;
}


