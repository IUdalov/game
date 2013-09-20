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

struct dCoord{
    double x,y;
};

struct Coord{
    int x,y;
};

struct pntRect{
    Coord x1, x2, x3, x4;
};

struct Rect{
    int left, right, top, bottom;
};

double MinXPntRect(pntRect r);
double MinYPntRect(pntRect r);
double MaxXPntRect(pntRect r);
double MaxYPntRect(pntRect r);

/*bool HitCrdPntRect(Coord crd, pntRect r){

}

bool HitPntRectRect(pntRect r1, pntRect r2){

}
*/

struct Cell{
    unsigned int			 CurNum;
    vector<IDn>		Objects;
    void*		 BackGround;
};

struct SysTimer{
    unsigned int MaxTime,
        CurTime;
};

//////////////////////////////////////
bool HitRectRect(const QRect& rect1,const QRect& rect2);
bool HitRectCrd(const QRect& rect,int  x, int y);

#endif // FORMULS_H
