#ifndef MODELS_DECLARATIONS
#define MODELS_DECLARATIONS

#include "../INDIan/core_includes.h"

enum{
    SE_STARTGAME = 101,
    SE_CREATEFIELD,
    SE_DELETEFIELD,
    SE_FIELDPARAM,
    SE_FIELD_SHINE_LEFT,
    SE_FIELD_SHINE_RIGHT,
    SE_FIELD_SHINE_CLOSE,
    SE_INITSELECTOR,
    SE_NEXTGAMEPART,
    SE_REPLAY,
    SE_ENDGAME
};

enum{
    STO_SYSTEM	=	0,
    STO_CHEKERS,
    STO_FIELD,
    STO_MENU,
    STO_ARROWS
};

enum{
    ID_BMP_EMPTY	=	0,
    ID_BMP_BIG_CHEKER,
    ID_BMP_MID_CHEKER,
    ID_BMP_SMALL_CHEKER,
    ID_BMP_BIG_CHEKER2,
    ID_BMP_MID_CHEKER2,
    ID_BMP_SMALL_CHEKER2,
    ID_BMP_SELECTOR_BIG,
    ID_BMP_SELECTOR_MIDDLE,
    ID_BMP_SELECTOR_SMALL,
    ID_BMP_ARROW,
    ID_BMP_CELL,
    ID_BMP_CELL_SHINE1,
    ID_BMP_CELL_SHINE2,
    ID_BMP_CELL_SHINE3,
    ID_BMP_BTNPLAY,

    ID_BMP_MENU_PLAY,
    ID_BMP_RULES,
    ID_BMP_OPTIONS,
    ID_BMP_EXIT,
    ID_BMP_BACK,
    ID_BMP_PLAY,
    ID_BMP_PAUSE,
    ID_BMP_RESTART,

//    ID_BMP_EXAMPLE,

    NumTileRes
};

//////////////////////////////////////////////////////////////////////////////////

struct GameParam{
    //++параметры поля
    int FieldWidth, FieldHeight;
    //--
    int big_num;
    int midle_num;
    int small_num;
};

enum Global_const {
    DRAW_FIELD = 0,
    DRAW_SELECTOR,
    DRAW_CHECKER,
    DRAW_ARROW,
    DRAW_MENU,
    DRAW_LEVELS
};

enum CheckersType{
    big = 0,
    middle,
    small
};

INDIan::GEO_SCAN_STATUS gps_for_menu_rect(INDIan::GEO_SCAN_TYPE geo_pr_type, INDIan::Object obj, void* geo_pr_data);
INDIan::GEO_SCAN_STATUS gps_for_menu_circle(INDIan::GEO_SCAN_TYPE geo_pr_type, INDIan::Object obj, void* geo_pr_data);
INDIan::GEO_SCAN_STATUS gps_for_checker(INDIan::GEO_SCAN_TYPE geo_pr_type, INDIan::Object obj, void* geo_pr_data);

void initImages();

#endif
