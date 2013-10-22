#ifndef TRANSPORT_H
#define TRANSPORT_H

#include "formuls.h"

class MainWindow;
class System_ROOT;
class Model_Objects;
class cResources;
class xBmp;
class Obj_Manager;
class CObj;

//системные сообщения (Main Event)
enum{
    ME_KEYUP =	1,
    ME_KEYDOWN,
    ME_TIMER,
    ME_DRAW,
    ME_CREATE,
    ME_MOUSECLICK,
    ME_MOUSEMOVE
};

//геометрия
enum GEO_TYPE{
    GEO_NONE = 0,
    GEO_BREP
};

// сообщения от менеджера объектов и структуры данных ими присылаемых
enum{
    OE_CLASH = 50,
    OE_MOUSECLICK,
    OE_MOUSEMOVE
};

struct OED_Clash{
    IDn id_dest;
    IDn id_src;
};
struct OED_Mouse{
    IDn idObj;
    sMouse mouse;
};

// геометрия
enum GEO_SCAN_STATUS{
    GSS_DO = 0x0001, // произвести автоматическое сканирование
    GSS_OK = 0x0002, // положительный ответ сканеру
    GSS_BREAK = 0x0004, // прервать работу сканера
    GSS_CONTINUE = 0x0008 // сканировать следующий элемент
};

enum GEO_SCAN_TYPE{
    GST_BREP_BREP = 0, // сканируем два брепа
    GST_BREP_PNT // сканируем бреп и точку
};

enum GEO_SCAN_ANS{
    GSA_CANCEL = 0,
    GSA_CONTINUE,
    GSA_OK
};

typedef GEO_SCAN_STATUS (*GEO_PRE_SCANER)(GEO_SCAN_TYPE geo_pr_type, CObj obj, void* geo_pr_data);

struct Geo{
    GEO_TYPE type;
    GEO_PRE_SCANER pre_processor;
};



#endif // TRANSPORT_H
