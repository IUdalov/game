#ifndef MODELS_H
#define MODELS_H

#include "core_includes.h"
#include "Formuls.h"
#include "Resources.h"
#include "Object.h"

class Model_Objects{
public:
    bool OnlyDraw;
    bool NotPaused;
private:
    unsigned int SubType;
    vector<IDn> ObjId;
    int SizeOfSubStr;
private:
    void Destroy(unsigned int num);
    void Plus(IDn ID);
    void DeleteObj(IDn ID);
    void AddObj(IDn ID);
public:
    Model_Objects(unsigned int _SubType,int _SizeOfSubStr);
    ~Model_Objects(void);
    void CreateSimpleObj(CObj* obj);
    virtual void EventsHandler(unsigned int mess,void* data);
    unsigned int GetVolume(void);
    unsigned int GetSubType();
    IDn operator[](unsigned int num);
    IDn GetObj(unsigned int num);
    friend class System_ROOT;
//    friend class Obj_Manager;
};


#endif // MODELS_H
