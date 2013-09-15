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
    RECT Rect;
    unsigned int image;
    unsigned int BMP;
private:
    Model_Objects* lpModel;
    unsigned long SubType;
    void* SubStr;
public:
    CObj(void);
    CObj(CObj& str);
    RECT GetRect();
    void Draw(void);
    void Draw(unsigned int _x,unsigned int _y);
    void DrawWithMove(int xm,int ym);
    CObj& operator=(const CObj& str);
    Model_Objects* GetLpModel(void);
    unsigned int GetSubType(void);
    void* GetSubStr(void);
    void SetRectByImage(void);
    friend class Model_Objects;
    friend class System_ROOT;
    friend class Obj_Manager;
};


#endif // OBJECT_H
