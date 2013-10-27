#ifndef FIELD_H
#define FIELD_H

#include "../inits/declarations.h"
#include "../INDIan/core_includes.h"
#include "../physics/physics.h"

using namespace INDIan;

class Field : public Model{
    vector<DCoord> topCrdV;
    vector<DCoord> leftCrdV;
    vector<DCoord> rightCrdV;
    vector<DCoord> bottomCrdV;
    Rect fieldRect;
    int gridWidth;
    int gridHeight;
public:
    Field();
    virtual ~Field();
    virtual void EventsHandler(int mess, void *data);
    void CreateShineField(int part);
};


#endif // FIELD_H
