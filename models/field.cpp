#include "field.h"

Field field;

Field::Field() : Model_Objects(STO_FIELD, 0){
}
Field::~Field(){
}
void Field::EventsHandler(unsigned int mess, void *data){
    int PoleWidth, PoleHeight;
    CObj obj;
    IDn id;
    Rect* r;
    switch(mess){
    case SE_CREATEFIELD:
        if(!data)
            return;
        PoleWidth = *((int*)data);
        PoleHeight = *(((int*)data) + 1);

        this->CreateSimpleObj(&obj);
        obj.BMP = ID_BMP_CELL;
        int x, y, width, height;
        width = Resources.Get_BMP(ID_BMP_CELL)->GetWidth();
        height = Resources.Get_BMP(ID_BMP_CELL)->GetHeight();
        x = Root.GetScreenWidth() / 2 - (width * PoleWidth / 2);
        y = Root.GetScreenHeight() / 2 - (height * PoleHeight / 2);
        obj.image = 0;
        obj.SetRectByImage();
        obj.LevelOfDraw = 0;
        for(int i = 0 ; i < PoleWidth; i ++){
            for(int j = 0 ; j < PoleHeight; j ++){
                obj.x = x + ((double)i + 0.5) * width;
                obj.y = y + ((double)j + 0.5) * height;
                ObjManager.CreateObj(obj, id);
                ObjManager.AddToGrid(id, false);
            }
        }
        r = (Rect*)Root.PutEventToQueue(sizeof(Rect), SE_FIELDPARAM, STO_CHEKERS);
        r->left = x;
        r->right = x + PoleWidth * width;
        r->top = y;
        r->bottom = y + PoleHeight * height;
        break;
    case SE_DELETEFIELD:
        while(this->GetVolume())
            ObjManager.DeleteObj(this->GetObj(0));
        break;
    default:
        break;
    }
}
