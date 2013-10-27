#include "menu.h"

Menu::Menu() : Model(STO_MENU, 0), currMenu(Start) {
}
Menu::~Menu(){
}

void Menu::EventsHandler(int mess, void* data) {
    switch(mess){
    case ME_CREATE:
    {
        ObjManager::ReBuildGrid(GLWindow::GetScreenWidth() / 50 + 1,
                                GLWindow::GetScreenHeight() / 50 + 1, 50, 50, 0);
        Root::numLevelDraw = DRAW_LEVELS;

        InitMenuItems();
        ShowStartMenu();
        currMenu = Start;
    }
        break;
    case OE_MOUSECLICK:
    {
        MouseClick(((OEDMouse*)data)->idObj, ((OEDMouse*)data)->mouse);
    }
        break;
    default:
        ;
    }
    return;
}

void Menu::ShowMenuItem(int item) {
     ObjManager::AddToGrid((*menuItems.find(item)).second, false);
     return;
}

void Menu::HideMenuItem(int item) {
    ObjManager::DeleteFromGrid((*menuItems.find(item)).second);
    return;
}

void Menu::MouseClick(IDn objId, SMouse mouse) {
    Object obj;
    if(!ObjManager::GetObj(objId, obj))
        return;

    if(mouse.L == Root::S_DOWN) {
        switch (obj.tileId) {
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
            Root::CloseApp();
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
                Root::PutEventToQueue(0, SE_ENDGAME, STO_CHEKERS);
                break;
            default:
                ;
            }
            currMenu = Start;
            ShowStartMenu();
            break;

        case ID_BMP_PLAY:{
            if (currMenu == Position) {
                HidePositionMenu();
                currMenu = GameActive;
                GameParam* gameparam;
                gameparam = (GameParam*)Root::PutEventToQueue(sizeof(GameParam), SE_STARTGAME, STO_CHEKERS);
                gameparam->FieldWidth = gameparam->FieldHeight = 8;
                gameparam->big_num = 4;
                gameparam->midle_num = 4;
                gameparam->small_num = 4;
                ShowGameMenu();
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
            HidePauseMenu();;
            currMenu = GameActive;
            ShowGameMenu();
            Root::PutEventToQueue(0, SE_REPLAY, STO_CHEKERS);
            break;

        default:
            ;
        }
    }
// delete
    return;
}


