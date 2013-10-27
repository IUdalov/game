#include "models.h"

namespace INDIan{
    void Model::Destroy(int num){
        objId.erase(objId.begin()+num);
    }
    void Model::DeleteObj(IDn ID){
        for(int i = 0; i < (int)objId.size(); i++){
            if(objId[i] == ID){
                Destroy(i);
                return;
            }
        }
    }
    void Model::DeleteObj(int i){
        if( (i >= 0) && (i < (int)objId.size())){
           Destroy(i);
        }
    }
    int Model::SaveObj(IDn ID){
        objId.push_back(ID);
        return objId.size() - 1;
    }
    Model::Model(int _subType,int _sizeOfSubStr){
        subType = _subType;
        sizeOfSubStr = _sizeOfSubStr;
        onlyDraw = notPaused = false;
    }
    Model::~Model(void){
        objId.clear();
    }
    void Model::EventsHandler(int mess,void* data){
    }
    int Model::GetVolume(void){
        return objId.size();
    }
    int Model::GetSubType(){
        return subType;
    }
    IDn Model::operator[](int num){
        return objId[num];
    }
    IDn Model::GetObj(int num){
        return objId[num];
    }
}
