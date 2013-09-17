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

