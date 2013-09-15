#ifndef FORMULS_H
#define FORMULS_H

#include "dependences.h"

#define MAX(a, b)			( (a) > (b) ? (a) : (b) )
#define MIN(a, b)			( (a) < (b) ? (a) :(b) )
#define IND(i, j, line)	( (i) + (j )* (line) )

//class Model_Objects;
//class System_ROOT;
//class Obj_Manager;

struct IDn{
    unsigned int ID;
    unsigned int DateBorn;
};

struct RECT{
    int left, right, top, bottom;
};
struct Cell{
    unsigned int			 CurNum;
    vector<IDn>		Objects;
    void*		 BackGround;
};

struct COORD{
    int x,y;
};

typedef struct Double_COORD_STRUCT{
    double x;
    double y;
}dCOORD;

typedef struct Double_RECT_STRUCT{
    double left,right,top,bottom;
}dRECT;

struct SysTimer{
    unsigned int MaxTime,
        CurTime;
};

//////////////////////////////////////
bool HitRectRect(const RECT& rect1,const RECT& rect2);
bool HitRectCrd(const RECT& rect,int  x, int y);

#endif // FORMULS_H
