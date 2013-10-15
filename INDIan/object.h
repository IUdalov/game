#ifndef OBJECT_H
#define OBJECT_H

#include "dependences.h"
#include "formuls.h"
#include "resources.h"

class Model_Objects;

class CObj{
public:
    unsigned int LevelOfDraw;
    double x,y;
    unsigned int image;
    unsigned int BMP;
private:
    pntRect rect;
    int Width, Height;
    float angle;
    Model_Objects* lpModel;
    unsigned long SubType;
    void* SubStr;
    bool isTurned;

    Coord TurnPoint(Coord crd, Coord crd2, float angle);
public:
    CObj(void);
    CObj(const CObj& str);
    pntRect GetPntRect();
    Rect GetRect();
    void Draw(void);
    void Draw( int _x, int _y);
    void DrawWithMove(int xm,int ym);
    CObj& operator=(const CObj& str);
    Model_Objects* GetLpModel(void);
    unsigned int GetSubType(void);
    void* GetSubStr(void);
    void SetWidthHeight(int width, int height);
    void SetDefaultAngle(void);
    void SetRectByImage(void);
    void TurnImage(float angle);
    bool HitPoint(Coord pnt);
    bool HitRect(Rect rect);
    int GetWidth();
    int GetHeight();
    void SetBmp(unsigned int id_bmp, bool setRectByImage = true );
    friend class Model_Objects;
    friend class System_ROOT;
    friend class Obj_Manager;
};


#endif // OBJECT_H
