#include "object.h"
//#include "resources.h"

extern cResources Resources;

CObj::CObj(void){
    x = 0;
    y = 0;
    Rect = QRect(0, 0, 0, 0);
    image = 0;
    SubType = 0;
    lpModel = NULL;
    LevelOfDraw = 0;
    BMP = 0;
    SubStr = NULL;
}
CObj::CObj(CObj& str){
    x = str.x;
    y = str.y;
    Rect = str.Rect;
    image = str.image;
    SubType = str.SubType;
    lpModel = str.lpModel;
    BMP = str.BMP;
    SubStr = str.SubStr;
    LevelOfDraw = str.LevelOfDraw;
}
QRect CObj::GetRect(){
    QRect rect;

    rect.setLeft(x + Rect.left());
    rect.setTop(y + Rect.top());
    rect.setRight(x + Rect.right());
    rect.setBottom(y + Rect.bottom());
    return rect;
}
void CObj::Draw(void){
    if(BMP){
        Resources.Get_BMP(BMP)->Draw(image, (int)x, (int)y);
    }
}
void CObj::Draw(unsigned int _x,unsigned int _y){
    if(BMP){
        Resources.Get_BMP(BMP)->Draw(image, _x, _y);
    }
}
void CObj::DrawWithMove(int xm,int ym){
    if(BMP){
        Resources.Get_BMP(BMP)->Draw(image, (int)x+xm, (int)y+ym);
    }
}
CObj& CObj::operator=(const CObj& str){
        x = str.x;
        y = str.y;
        image = str.image;
        Rect = str.Rect;
        SubType = str.SubType;
        BMP = str.BMP;
        lpModel = str.lpModel;
        SubStr = str.SubStr;
        LevelOfDraw = str.LevelOfDraw;
        return *this;
}
Model_Objects* CObj::GetLpModel(void){
    return lpModel;
}
unsigned int CObj::GetSubType(void){
    return SubType;
}
void* CObj::GetSubStr(void){
    return SubStr;
}
void CObj::SetRectByImage(void){
    if(BMP){
        Rect = QRect(0, 0,
            Resources.Get_BMP(BMP)->GetWidth() - 1,
            Resources.Get_BMP(BMP)->GetHeight() - 1);
    }
}

