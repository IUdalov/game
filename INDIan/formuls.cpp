#include "formuls.h"

namespace INDIan{
    bool HitRectRect(const QRect& rect1,const QRect& rect2){
        if( (rect1.left() <= rect2.right()) &&
                (rect1.top() <= rect2.bottom()) &&
                (rect1.right() >= rect2.left()) &&
                (rect1.bottom() >= rect2.top()))
            return true;
        return false;
    }
    bool HitRectRect(const Rect& rect1,const Rect& rect2){
        if( (rect1.left <= rect2.right) &&
                (rect1.top <= rect2.bottom) &&
                (rect1.right >= rect2.left) &&
                (rect1.bottom >= rect2.top))
            return true;
        return false;
    }

    bool HitRectCrd(const QRect& rect,int  x, int y){
        if( (x >= rect.left()) && (x <= rect.right())
                && (y >= rect.top()) && (y <= rect.bottom()) )
            return true;
        return false;
    }
    bool HitRectCrd(const Rect& rect,int  x, int y){
        if( (x >= rect.left) && (x <= rect.right)
                && (y >= rect.top) && (y <= rect.bottom) )
            return true;
        return false;
    }
    bool HitCircleCrd(int xc, int yc, int radius, int  xp, int yp){
        if( sqrt( pow( xc - xp,2.) + pow( yc - yp,2.) ) <= radius)
            return true;
        return false;
    }

    double MinXPntRect(PntRect r){
        return MIN( r.x1.x, MIN( r.x2.x, MIN(r.x3.x, r.x4.x)));
    }
    double MinYPntRect(PntRect r){
        return MIN( r.x1.y, MIN( r.x2.y, MIN(r.x3.y, r.x4.y)));
    }
    double MaxXPntRect(PntRect r){
        return MAX( r.x1.x, MAX( r.x2.x, MAX(r.x3.x, r.x4.x)));
    }
    double MaxYPntRect(PntRect r){
        return MAX( r.x1.y, MAX( r.x2.y, MAX(r.x3.y, r.x4.y)));
    }
    DCoord vect_norm(DCoord crd){
        DCoord res;
        double d = sqrt( pow( crd.x, 2.) + pow( crd.y, 2.));
        res.x = crd.x / d;
        res.y = crd.y / d;
        return res;
    }
    DCoord vect_mult_d(DCoord crd, double d){
        DCoord res;
        res.x = crd.x * d;
        res.y = crd.y * d;
        return res;
    }
    DCoord vect_null(void){
        DCoord res;
        res.x = 0;
        res.y = 0;
        return res;
    }
    DCoord vect_min(DCoord crd1, DCoord crd2){
        DCoord res;
        res.x = crd1.x - crd2.x;
        res.y = crd1.y - crd2.y;
        return res;
    }
    DCoord vect_sum(DCoord crd1, DCoord crd2){
        DCoord res;
        res.x = crd1.x + crd2.x;
        res.y = crd1.y + crd2.y;
        return res;
    }
    Coord TurnPoint(Coord crd1, Coord crd2, float angle){
        float xt = (float)crd2.x + ((float)(crd1.x - crd2.x)) * cos(angle) + ((float)(crd2.y - crd1.y)) * sin(angle);
        float yt = (float)crd2.y + ((float)(crd1.x - crd2.x)) * sin(angle) + ((float)(crd1.y - crd2.y)) * cos(angle);

        crd1.x = xt;
        crd1.y = yt;
        return crd1;
    }
    DCoord TurnPoint(DCoord crd1, DCoord crd2, float angle){
        float xt = (float)crd2.x + ((float)(crd1.x - crd2.x)) * cos(angle) + ((float)(crd2.y - crd1.y)) * sin(angle);
        float yt = (float)crd2.y + ((float)(crd1.x - crd2.x)) * sin(angle) + ((float)(crd1.y - crd2.y)) * cos(angle);

        crd1.x = xt;
        crd1.y = yt;
        return crd1;
    }
}



