#include "object.h"
//#include "resources.h"

extern cResources Resources;

CObj::CObj(void){
    angle = 0.;
    x = 0;
    y = 0;
    memset(&rect, 0, sizeof(pntRect));
    image = 0;
    SubType = 0;
    lpModel = NULL;
    LevelOfDraw = 0;
    BMP = 0;
    SubStr = NULL;
    isTurned = false;
    Width = 0;
    Height = 0;
}
CObj::CObj(const CObj& str){
    x = str.x;
    y = str.y;
    memcpy(&rect, &str.rect, sizeof(pntRect));
    image = str.image;
    SubType = str.SubType;
    lpModel = str.lpModel;
    BMP = str.BMP;
    SubStr = str.SubStr;
    LevelOfDraw = str.LevelOfDraw;
    isTurned = str.isTurned;
    Width = str.Width;
    Height = str.Height;
}
pntRect CObj::GetRect(){
    pntRect r;

    r.x1.x = x + rect.x1.x;
    r.x1.y = y + rect.x1.y;

    r.x2.x = x + rect.x2.x;
    r.x2.y = y + rect.x2.y;

    r.x3.x = x + rect.x3.x;
    r.x3.y = y + rect.x3.y;

    r.x4.x = x + rect.x4.x;
    r.x4.y = y + rect.x4.y;

    return r;
}
void CObj::Draw(void){
    if(BMP){
        pntRect r;
        r = GetRect();
        Resources.Get_BMP(BMP)->Draw(image, r.x1, r.x2, r.x3, r.x4);
    }
}
void CObj::Draw(unsigned int _x,unsigned int _y){
    if(BMP){
        double old_x = x;
        double old_y = y;

        x = _x;
        y = _y;

        Draw();

        x = old_x;
        y = old_y;

    }
}
void CObj::DrawWithMove(int xm,int ym){
    if(BMP){
        Draw( (int)x+xm, (int)y+ym);
    }
}
CObj& CObj::operator=(const CObj& str){
        x = str.x;
        y = str.y;
        image = str.image;
        memcpy(&rect, &str.rect, sizeof(pntRect));
        SubType = str.SubType;
        BMP = str.BMP;
        lpModel = str.lpModel;
        SubStr = str.SubStr;
        LevelOfDraw = str.LevelOfDraw;
        Width = str.Width;
        Height = str.Height;
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
        Width = Resources.Get_BMP(BMP)->GetWidth();
        Height = Resources.Get_BMP(BMP)->GetHeight();
        SetDefaultAngle();
    }
}
Coord CObj::TurnPoint(Coord crd1, Coord crd2, float angle){
    isTurned = true;

    float xt = (float)crd2.x + ((float)(crd1.x - crd2.x)) * cos(angle) + ((float)(crd2.y - crd1.y)) * sin(angle);
    float yt = (float)crd2.y + ((float)(crd1.x - crd2.x)) * sin(angle) + ((float)(crd1.y - crd2.y)) * cos(angle);

    crd1.x = xt;
    crd1.y = yt;
    return crd1;
}
void CObj::TurnImage(float angle){
    SetDefaultAngle();

    Coord crd;
    crd.x = 0;
    crd.y = 0;

    rect.x1 = TurnPoint(rect.x1, crd, angle);
    rect.x2 = TurnPoint(rect.x2, crd, angle);
    rect.x3 = TurnPoint(rect.x3, crd, angle);
    rect.x4 = TurnPoint(rect.x4, crd, angle);
}
void CObj::SetWidthHeight(int width, int height){
    Width = width;
    Height = height;
    SetDefaultAngle();
}
void CObj::SetDefaultAngle(void){
    isTurned = false;

    int width2 = Width / 2;
    int height2 = Height / 2;
    int width1 = (Width % 2 == 0) ? width2 - 1 : width2;
    int height1 = (Height % 2 == 0) ? height2 - 1 : height2;

    rect.x1.x = - width1;
    rect.x1.y = - height1;

    rect.x2.x = width2;
    rect.x2.y = - height1;

    rect.x3.x = width2;
    rect.x3.y = height2;

    rect.x4.x = - width1;
    rect.x4.y = height2;
}
bool CObj::HitPoint(Coord pnt){
    if(isTurned)
        return false;

    Rect r;
    pntRect prect = GetRect();
    r.left = prect.x1.x;
    r.right = prect.x2.x;
    r.top = prect.x1.y;
    r.bottom = prect.x3.y;

    if( (pnt.x >= r.left) && (pnt.x <= r.right) && (pnt.y >= r.top) &&  (pnt.y <= r.bottom))
        return true;
    return false;
}
bool CObj::HitRect(Rect rect){
    if(isTurned)
        return false;
    return true;
}
int CObj::GetWidth(){
    return Width;
}
int CObj::GetHeight(){
    return Height;
}





