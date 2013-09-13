#include "Resources.h"

cResources Resources;

cResources::cResources(){ fail = false;}
cResources::~cResources(){}
void cResources::AddBmpFiles(void){

}
void cResources::EndBmpSystem(void){
    for(unsigned int i=0;i<BmpDim.size();i++)
        if(BmpDim[i])
            delete BmpDim[i];
    BmpDim.clear();
}
void cResources::Add_BMP(unsigned int ID_BMP, QString file_name, QString mask_filename, unsigned int Volume, unsigned int colums, unsigned int lines){
    if(ID_BMP < 1 || ID_BMP >= NumBmpRes)
        return;
    xBmp* New;
    if(BmpDim[ID_BMP])
        New = BmpDim[ID_BMP];
    else{
        New = new xBmp;
        BmpDim[ID_BMP] = New;
    }
    if(!New->Create(file_name,mask_filename,Volume,colums,lines)){
        delete New;
        New = NULL;
        fail = true;
        BmpDim[ID_BMP] = NULL;
    }
}
bool cResources::StartBmpSystem(void){
    EndBmpSystem();
    BmpDim.resize(NumBmpRes);
    for(unsigned int i = 0 ; i < BmpDim.size(); i++)
        BmpDim[i] = NULL;
    AddBmpFiles();
    return !fail;
}
bool cResources::Init_Resource(void){
    if(!StartBmpSystem())
        return false;
    return true;
}
xBmp* cResources::Get_BMP(unsigned int num){
    if(num < 1 || num >= NumBmpRes)
        return NULL;
    return	BmpDim[num];
}
int cResources::GetBmpCount(){
    return BmpDim.size();
}
void cResources::DisResources(){
    EndBmpSystem();
}

