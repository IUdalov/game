#ifndef EXAMPLE_MODEL_H
#define EXAMPLE_MODEL_H

#include "INDIan/core_includes.h"

extern System_ROOT Root;
extern int ScreenWidth;
extern int ScreenHeight;
extern cResources Resources;
extern Obj_Manager ObjManager;

class cExample : Model_Objects{
public:
    Coord step;
    short CheckEnable;
    CObj arrow;

    cExample();
    ~cExample();
    virtual void EventsHandler(unsigned int mess, void *data);
};

#endif // EXAMPLE_MODEL_H
