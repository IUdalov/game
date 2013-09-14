#include "models.h"


vector<Model_Objects*> DimOfModels;

void Model_Objects::Destroy(unsigned int num){
    ObjId.erase(ObjId.begin()+num);
}
void Model_Objects::Plus(IDn ID){
    ObjId.push_back(ID);
}
void Model_Objects::DeleteObj(IDn ID){
    for(unsigned int i = 0; i < ObjId.size(); i++){
        if((ObjId[i].ID == ID.ID)&&(ObjId[i].DateBorn == ID.DateBorn)){
            Destroy(i);
            return;
        }
    }
}
void Model_Objects::AddObj(IDn ID){
    Plus(ID);
}
Model_Objects::Model_Objects(unsigned int _SubType,int _SizeOfSubStr){
    SubType = _SubType;
    SizeOfSubStr = _SizeOfSubStr;
    OnlyDraw = NotPaused=false;
    DimOfModels.push_back(this);
}
Model_Objects::~Model_Objects(void){
    ObjId.clear();
}
void Model_Objects::CreateSimpleObj(CObj* obj){
    obj->lpModel = this;
    obj->SubType = SubType;
    if(SizeOfSubStr)
        obj->SubStr = malloc(SizeOfSubStr);
}
void Model_Objects::EventsHandler(unsigned int mess,void* data){
}
unsigned int Model_Objects::GetVolume(void){
    return ObjId.size();
}
unsigned int Model_Objects::GetSubType(){
    return SubType;
}
IDn Model_Objects::operator[](unsigned int num){
    return ObjId[num];
}
IDn Model_Objects::GetObj(unsigned int num){
    return ObjId[num];
}

