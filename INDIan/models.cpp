#include "core_includes.h"

namespace INDIan{
    Model::Model(int _subType,int _sizeOfSubStr){
        subType = _subType;
        sizeOfSubStr = _sizeOfSubStr;
        onlyDraw = notPaused = false;
        objId.resize(1);
    }
    Model::~Model(void){
        objId.clear();
    }
    void Model::EventsHandler(int mess,void* data){
    }
    void Model::CompliteContainers(int size){
        if(size < 0)
            return;
        else if(size > (int)objId.size())
            objId.resize(size);
        else
            return;
    }

    int Model::GetVolume(int container){
        CompliteContainers(container);
        return objId[container].size();
    }
    int Model::GetSubType(){
        return subType;
    }
    IDn Model::GetObj(int num, int container){
        return objId[container][num];
    }
    void Model::Destroy(int num, int container){
        objId[container].erase(objId[container].begin()+num);
    }
    void Model::DeleteObj(IDn ID, int container){
        int firstCont = 0, lastCont = 0;
        if(container == IN_ALL_CONTAINERS)
            lastCont = (int)objId.size() - 1;
        else
            firstCont = lastCont = container;

        for(int i = firstCont; i <= lastCont; i++){
            for(int j = 0; j < (int)objId[i].size(); j++){
                if(objId[i][j] == ID){
                 Destroy(j, i);
                 return;
                }
            }
        }
    }
    void Model::DeleteObj(int i, int container){
           Destroy(i, container);
    }
    int Model::SaveObj(IDn ID, int container){
        CompliteContainers(container);
        objId[container].push_back(ID);
        return objId[container].size() - 1;
    }
    vector<IDn>& Model::GetContainer(int num){
        return objId[num];
    }
    void Model::ClearContainer(int num){
        objId[num].clear();
    }
}
