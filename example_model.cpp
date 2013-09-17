#include "example_model.h"

cExample Example;

cExample::cExample() : Model_Objects(1,0){

}
cExample::~cExample(){

}
void cExample::EventsHandler(unsigned int mess, void *data){
    CObj obj;
    IDn ID;
    switch(mess){
    case ME_CREATE:
        ObjManager.ReBuildGrid(10, 10, 50, 50, 0);
        Root.NumLevelDraw = 1;
        this->CreateSimpleObj(&obj);
        obj.x = 0;
        obj.y = 0;
        obj.BMP = ID_BMP_BACKGROUND;
        obj.image = 0;
        obj.SetRectByImage();
        ObjManager.CreateObj(obj, ID);
        ObjManager.AddToGrid(ID, false);
        break;
    case ME_DRAW:
//        ObjManager.GetObj(this->GetObj(0),obj);
//        obj.Draw();
        break;
    case ME_KEYDOWN:
        if(*((int*)data) == Qt::Key_Right){
            ObjManager.GetObj(this->GetObj(0),obj);
            obj.x += 10;
            ObjManager.ChangeObj(this->GetObj(0), obj);
        }
        else if(*((int*)data) == Qt::Key_Escape)
            Root.CloseApp();
        break;
    }
}
