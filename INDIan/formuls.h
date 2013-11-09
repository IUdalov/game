#ifndef FORMULS_H
#define FORMULS_H

#include "dependences.h"

#define MAX(a, b)			( (a) > (b) ? (a) : (b) )
#define MIN(a, b)			( (a) < (b) ? (a) :(b) )
#define IND(i, j, line)	( (i) + (j )* (line) )

namespace INDIan{
    struct SMouse{
        short L,R,M;
        GLuint x,y;
    };

    struct IDn{
        int id;
        int dateBorn;
        bool operator==(const IDn& idn){
            if( (id == idn.id) && (dateBorn == idn.dateBorn) )
                return true;
            return false;
        }
    };

    struct DCoord{
        double x,y;
    };

    struct Coord{
        int x,y;
    };

    struct PntRect{
        Coord x1, x2, x3, x4;
    };

    struct Rect{
        int left, right, top, bottom;
    };

    double MinXPntRect(PntRect r);
    double MinYPntRect(PntRect r);
    double MaxXPntRect(PntRect r);
    double MaxYPntRect(PntRect r);

    /*bool HitCrdPntRect(Coord crd, pntRect r){

    }

    bool HitPntRectRect(pntRect r1, pntRect r2){

    }
    */

    struct Cell{
        int curNum;
        vector<IDn> objects;
        void* backGround;
    };

    struct SysTimer{
        int MaxTime,
            CurTime;
    };

    //////////////////////////////////////
    bool HitRectRect(const QRect& rect1,const QRect& rect2);
    bool HitRectCrd(const QRect& rect,int  x, int y);

    bool HitRectRect(const Rect& rect1,const Rect& rect2);
    bool HitRectCrd(const Rect& rect,int  x, int y);
    bool HitCircleCrd(int xc, int yc, int radius, int  xp, int yp);

    DCoord vect_norm(DCoord crd);
    DCoord vect_mult_d(DCoord crd, double d);
    DCoord vect_null(void);
    DCoord vect_min(DCoord crd1, DCoord crd2);
    DCoord vect_sum(DCoord crd1, DCoord crd2);

    Coord TurnPoint(Coord crd1, Coord crd2, float angle);
    DCoord TurnPoint(DCoord crd1, DCoord crd2, float angle);
}
#endif // FORMULS_H
