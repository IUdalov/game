 #ifndef MODELS_H
#define MODELS_H

#include "transport.h"
#include "dependences.h"
#include "formuls.h"


namespace INDIan{
    class Model{
    enum{
        BASE_CONTAINER = 0,
        IN_ALL_CONTAINERS = -1
    };
    public:
        bool onlyDraw;
        bool notPaused;
    private:
        int subType;
        vector< vector<IDn> > objId;
        int sizeOfSubStr;

        void Destroy(int i, int container);
        void CompliteContainers(int size);
    public:
        Model(int _subType,int _sizeOfSubStr);
        ~Model(void);
        virtual void EventsHandler(int mess,void* data);
        int GetVolume(int container = BASE_CONTAINER);
        int GetSubType();
        IDn GetObj(int num, int container = BASE_CONTAINER);
        void DeleteObj(IDn ID, int container = IN_ALL_CONTAINERS);
        void DeleteObj(int i, int container = BASE_CONTAINER);
        int SaveObj(IDn ID, int container = BASE_CONTAINER);
        vector<IDn>& GetContainer(int num = BASE_CONTAINER);
        void ClearContainer(int num = BASE_CONTAINER);
    };
}

#endif // MODELS_H
