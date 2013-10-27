#ifndef OBJECT_H
#define OBJECT_H

#include "dependences.h"
#include "formuls.h"
#include "resources.h"

namespace INDIan{
    class Object{
    public:
        int levelOfDraw;
        double x,y;
        int image;
        int tileId;
        Geo geo;
        long subType;
        int sizeOfSubStr;
        void* subStr;
    private:
        PntRect rect;
        int width, height;
        float angle;
        bool isTurned;

        Coord TurnPoint(Coord crd, Coord crd2, float angle);
    public:
        Object(void);
        Object(const Object& str);
        PntRect GetPntRect();
        Rect GetRect();
        void Draw(void);
        void Draw( int _x, int _y);
        void DrawWithMove(int xm,int ym);
        Object& operator=(const Object& str);
        void SetWidthHeight(int width, int height);
        void SetDefaultAngle(void);
        void SetRectByImage(void);
        void TurnImage(float angle);
        bool HitPoint(Coord pnt);
        bool HitRect(Rect rect);
        int GetWidth();
        int GetHeight();
        void SetTile(int idTile, bool setRectByImage = true );
    };
}
#endif // OBJECT_H
