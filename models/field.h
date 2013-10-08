#ifndef FIELD_H
#define FIELD_H

#include "../inits/declarations.h"
#include "../INDIan/core_includes.h"
#include "../physics/physics.h"

extern System_ROOT Root;
extern int ScreenWidth;
extern int ScreenHeight;
extern cResources Resources;
extern Obj_Manager ObjManager;

class Field : public Model_Objects{
public:
    Field();
    virtual ~Field();
    virtual void EventsHandler(unsigned int mess, void *data);
};


#endif // FIELD_H
