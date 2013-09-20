#include "formuls.h"

bool HitRectRect(const QRect& rect1,const QRect& rect2){
    if( (rect1.left() <= rect2.right()) &&
            (rect1.top() <= rect2.bottom()) &&
            (rect1.right() >= rect2.left()) &&
            (rect1.bottom() >= rect2.top()))
        return true;
    return false;
}

bool HitRectCrd(const QRect& rect,int  x, int y){
    if( (x >= rect.left()) && (x <= rect.right())
            && (y >= rect.top()) && (y <= rect.bottom()) )
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

