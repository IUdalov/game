#ifndef MODELS_DECLARATIONS
#define MODELS_DECLARATIONS
enum{
    SE_STARTGAME = 101,
    SE_CREATEFIELD,
    SE_DELETEFIELD,
    SE_FIELDPARAM,
    SE_INITSELECTOR,
    SE_NEXTGAMEPART
};

enum{
    STO_SYSTEM	=	0,
    STO_CHEKERS,
    STO_FIELD
};

enum{
    ID_BMP_EMPTY	=	0,
    ID_BMP_BIG_CHEKER,
    ID_BMP_MID_CHEKER,
    ID_BMP_SMALL_CHEKER,
    ID_BMP_BIG_CHEKER2,
    ID_BMP_MID_CHEKER2,
    ID_BMP_SMALL_CHEKER2,
    ID_BMP_ARROW,
    ID_BMP_CELL,
    ID_BMP_BTNPLAY,
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

enum CheckersType{
    big = 0,
    middle,
    small
};

#endif
