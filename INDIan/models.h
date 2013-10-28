#ifndef MODELS_H
#define MODELS_H

#include "transport.h"
#include "dependences.h"
#include "formuls.h"


namespace INDIan{
    class Model{
    public:
        bool onlyDraw;
        bool notPaused;
    private:
        int subType;
        vector<IDn> objId;
        int sizeOfSubStr;

        void Destroy(int i);
    public:
        Model(int _subType,int _sizeOfSubStr);
        ~Model(void);
        virtual void EventsHandler(int mess,void* data);
        int GetVolume(void);
        int GetSubType();
        IDn operator[](int num);
        IDn GetObj(int num);
        void DeleteObj(IDn ID);
        void DeleteObj(int i);
        int SaveObj(IDn ID);
    };
}

#endif // MODELS_H
