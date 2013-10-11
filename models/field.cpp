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
        obj.y = y + (int)(0.5 * (double)height);
        for(int i = 0 ; i < PoleWidth; i ++){
            if(i == 0){
                obj.image = 6;
            }
            else if(i == PoleWidth - 1){
                obj.image = 8;
            }
            else{
                obj.image = 7;
            }
            obj.x = x + ((double)i + 0.5) * width;
            ObjManager.CreateObj(obj, id);
            ObjManager.AddToGrid(id, false);
        }
        obj.y = y + height * PoleHeight - 0.5 *height;
        for(int i = 0 ; i < PoleWidth; i ++){
            if(i == 0){
                obj.image = 0;
            }
            else if(i == PoleWidth - 1){
                obj.image = 2;
            }
            else{
                obj.image = 1;
            }
            obj.x = x + ((double)i + 0.5) * width;
            ObjManager.CreateObj(obj, id);
            ObjManager.AddToGrid(id, false);
        }
        for(int i = 0 ; i < (PoleHeight - 2); i ++){
            obj.image = 3;
            obj.x = x + 0.5 * width;
            obj.y = y + (1.5 + (float)i) *height;
            ObjManager.CreateObj(obj, id);
            ObjManager.AddToGrid(id, false);

            obj.image = 5;
            obj.x = x + width* PoleWidth - 0.5 * width;
            obj.y = y + (1.5 + (float)i) *height;
            ObjManager.CreateObj(obj, id);
            ObjManager.AddToGrid(id, false);
        }
/*        for(int i = 0 ; i < PoleWidth; i ++){
            for(int j = 0 ; j < PoleHeight; j ++){
                obj.x = x + ((double)i + 0.5) * width;
                obj.y = y + ((double)j + 0.5) * height;
                ObjManager.CreateObj(obj, id);
                ObjManager.AddToGrid(id, false);
            }
        }*/
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
