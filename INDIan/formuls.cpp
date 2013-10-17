#include "formuls.h"

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

double MinXPntRect(pntRect r){
    return MIN( r.x1.x, MIN( r.x2.x, MIN(r.x3.x, r.x4.x)));
}
double MinYPntRect(pntRect r){
    return MIN( r.x1.y, MIN( r.x2.y, MIN(r.x3.y, r.x4.y)));
}
double MaxXPntRect(pntRect r){
    return MAX( r.x1.x, MAX( r.x2.x, MAX(r.x3.x, r.x4.x)));
}
double MaxYPntRect(pntRect r){
    return MAX( r.x1.y, MAX( r.x2.y, MAX(r.x3.y, r.x4.y)));
}
dCoord vect_norm(dCoord crd){
    dCoord res;
    double d = sqrt( pow( crd.x, 2.) + pow( crd.y, 2.));
    res.x = crd.x / d;
    res.y = crd.y / d;
    return res;
}
dCoord vect_mult_d(dCoord crd, double d){
    dCoord res;
    res.x = crd.x * d;
    res.y = crd.y * d;
    return res;
}
dCoord vect_null(void){
    dCoord res;
    res.x = 0;
    res.y = 0;
    return res;
}
dCoord vect_min(dCoord crd1, dCoord crd2){
    dCoord res;
    res.x = crd1.x - crd2.x;
    res.y = crd1.y - crd2.y;
    return res;
}
dCoord vect_sum(dCoord crd1, dCoord crd2){
    dCoord res;
    res.x = crd1.x + crd2.x;
    res.y = crd1.y + crd2.y;
    return res;
}




