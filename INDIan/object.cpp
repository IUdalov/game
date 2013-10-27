#include "object.h"
//#include "resources.h"


namespace INDIan{
    Object::Object(void){
        angle = 0.;
        x = 0;
        y = 0;
        memset(&rect, 0, sizeof(PntRect));
        image = 0;
        subType = 0;
        levelOfDraw = 0;
        tileId = 0;
        subStr = NULL;
        sizeOfSubStr = 0;
        isTurned = false;
        width = 0;
        height = 0;
        geo.preScaner = NULL;
        geo.type = GEO_NONE;
    }
    Object::Object(const Object& str){
        x = str.x;
        y = str.y;
        memcpy(&rect, &str.rect, sizeof(PntRect));
        image = str.image;
        subType = str.subType;
        tileId = str.tileId;
        subStr = str.subStr;
        sizeOfSubStr = str.sizeOfSubStr;
        levelOfDraw = str.levelOfDraw;
        isTurned = str.isTurned;
        width = str.width;
        height = str.height;
        geo.preScaner = str.geo.preScaner;
        geo.type = str.geo.type;
    }
    Rect Object::GetRect(){
        Rect r;
        r.left = x + rect.x1.x;
        r.right = x + rect.x2.x;
        r.top = y + rect.x1.y;
        r.bottom = y + rect.x3.y;
        return r;
    }
    PntRect Object::GetPntRect(){
        PntRect r;

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
    void Object::Draw(void){
        if(tileId){
            PntRect r;
            r = GetPntRect();
            Resources::GetTile(tileId)->Draw(image, r.x1, r.x2, r.x3, r.x4);
        }
    }
    void Object::Draw( int _x,int _y){
        if(tileId){
            double old_x = x;
            double old_y = y;

            x = _x;
            y = _y;

            Draw();

            x = old_x;
            y = old_y;

        }
    }
    void Object::DrawWithMove(int xm,int ym){
        if(tileId){
            Draw( (int)x+xm, (int)y+ym);
        }
    }
    Object& Object::operator=(const Object& str){
            x = str.x;
            y = str.y;
            image = str.image;
            memcpy(&rect, &str.rect, sizeof(PntRect));
            subType = str.subType;
            tileId = str.tileId;
            subStr = str.subStr;
            sizeOfSubStr = str.sizeOfSubStr;
            levelOfDraw = str.levelOfDraw;
            width = str.width;
            height = str.height;
            geo.preScaner = str.geo.preScaner;
            geo.type = str.geo.type;
            return *this;
    }
    void Object::SetRectByImage(void){
        if(tileId){
            width = Resources::GetTile(tileId)->GetWidth();
            height = Resources::GetTile(tileId)->GetHeight();
            SetDefaultAngle();
        }
    }
    Coord Object::TurnPoint(Coord crd1, Coord crd2, float angle){
        isTurned = true;

        float xt = (float)crd2.x + ((float)(crd1.x - crd2.x)) * cos(angle) + ((float)(crd2.y - crd1.y)) * sin(angle);
        float yt = (float)crd2.y + ((float)(crd1.x - crd2.x)) * sin(angle) + ((float)(crd1.y - crd2.y)) * cos(angle);

        crd1.x = xt;
        crd1.y = yt;
        return crd1;
    }
    void Object::TurnImage(float angle){
        SetDefaultAngle();

        Coord crd;
        crd.x = 0;
        crd.y = 0;

        rect.x1 = TurnPoint(rect.x1, crd, angle);
        rect.x2 = TurnPoint(rect.x2, crd, angle);
        rect.x3 = TurnPoint(rect.x3, crd, angle);
        rect.x4 = TurnPoint(rect.x4, crd, angle);
    }
    void Object::SetWidthHeight(int width, int height){
        width = width;
        height = height;
        SetDefaultAngle();
    }
    void Object::SetDefaultAngle(void){
        isTurned = false;

        int width1 = width / 2;
        int height1 = height / 2;
        int width2 = (width % 2 == 0) ? width1: width1 + 1;
        int height2 = (height % 2 == 0) ? height1: height1 + 1;

        rect.x1.x = - width2;
        rect.x1.y = - height2;

        rect.x2.x = width1;
        rect.x2.y = - height2;

        rect.x3.x = width1;
        rect.x3.y = height1;

        rect.x4.x = - width2;
        rect.x4.y = height1;
    }
    bool Object::HitPoint(Coord pnt){
        if(isTurned)
            return false;

        Rect r;
        int width2 = width / 2;
        int height2 = height / 2;
        int width1 = (width % 2 == 0) ? width2 - 1 : width2;
        int height1 = (height % 2 == 0) ? height2 - 1 : height2;

        r.left = x - width1;
        r.right = x + width2;
        r.top = y - height1;
        r.bottom = y + height2;

        if( (pnt.x >= r.left) && (pnt.x <= r.right) && (pnt.y >= r.top) &&  (pnt.y <= r.bottom))
            return true;
        return false;
    }
    bool Object::HitRect(Rect rect){
        if(isTurned)
            return false;
        return true;
    }
    int Object::GetWidth(){
        return width;
    }
    int Object::GetHeight(){
        return height;
    }
    void Object::SetTile(int idTile, bool setRectByImage){
        tileId = idTile;
        if(setRectByImage)
            SetRectByImage();
    }
}





