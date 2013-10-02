#ifndef EXAMPLE_MODEL_H
#define EXAMPLE_MODEL_H

#include "../inits/declarations.h"
#include "../INDIan/core_includes.h"
#include "../physics/physics.h"

extern System_ROOT Root;
extern int ScreenWidth;
extern int ScreenHeight;
extern cResources Resources;
extern Obj_Manager ObjManager;

struct ObjChecker{
    double weight;
    dCoord vSpeed;
};

class cExample : Model_Objects{
public:
    short CheckEnable;
    vector<CObj> arrows;
    IDn CheckChecker;

    cExample();
    ~cExample();
    void CreateArrow( CObj& arrow, double x_c, double y_c, double x_l, double y_l, double length );
    virtual void EventsHandler(unsigned int mess, void *data);
};

#endif // EXAMPLE_MODEL_H
