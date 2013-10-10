#ifndef MODELS_DECLARATIONS
#define MODELS_DECLARATIONS
enum{
    SE_STARTGAME = 101,
    SE_CREATEFIELD,
    SE_DELETEFIELD,
    SE_FIELDPARAM,
    SE_INITSELECTOR,
    SE_NEXTGAMEPART,
    SE_REPLAY
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
    ID_BMP_BTNPLAY,

    ID_BMP_MENU_PLAY, // осн плей
    ID_BMP_RULES,
    ID_BMP_OPTIONS,
    ID_BMP_EXIT,

    ID_BMP_BACK,
    ID_BMP_PLAY,
    // где то здесь должны быть контролы генератора

    ID_BMP_PAUSE,
    ID_BMP_RESUME,
    ID_BMP_RESTART,

    NumBmpRes
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

#endif
