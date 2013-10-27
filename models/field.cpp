#include "field.h"

#define TIMER_ANIM 5

Field::Field() : Model(STO_FIELD, 0){
}
Field::~Field(){
}
void Field::EventsHandler(int mess, void *data){
    int PoleWidth, PoleHeight;
    Object obj;
    IDn id;
    Rect* r;
    switch(mess){
    case SE_CREATEFIELD:
        if(!data)
            return;
        Root::AddTimer(TIMER_ANIM);
        gridWidth = PoleWidth = *((int*)data);
        gridHeight = PoleHeight = *(((int*)data) + 1);
        topCrdV.clear(); leftCrdV.clear();
        rightCrdV.clear(); bottomCrdV.clear();

        DCoord crd;
        obj.tileId = ID_BMP_CELL;
        obj.subType = STO_FIELD;
        obj.sizeOfSubStr = 0;
        int x, y, width, height;
        width = Resources::GetTile(ID_BMP_CELL)->GetWidth();
        height = Resources::GetTile(ID_BMP_CELL)->GetHeight();
        x = GLWindow::GetScreenWidth() / 2 - (width * PoleWidth / 2);
        y = GLWindow::GetScreenHeight() / 2 - (height * PoleHeight / 2);
        obj.image = 0;
        obj.SetRectByImage();
        obj.levelOfDraw = 0;
        obj.y = y + 0.5 * height;
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
            obj.x = x + i * (width) + 0.5 * width;
            crd.x = obj.x; crd.y = obj.y;
            topCrdV.push_back(crd);
            ObjManager::CreateObj(obj, id);
            ObjManager::AddToGrid(id, false);
            this->SaveObj(id);
        }
        obj.y = y + (height) * (PoleHeight - 1 ) + 0.5 * height;
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
            obj.x = x + i * (width) + 0.5 * width;
            crd.x = obj.x; crd.y = obj.y;
            bottomCrdV.push_back(crd);
            ObjManager::CreateObj(obj, id);
            ObjManager::AddToGrid(id, false);
            this->SaveObj(id);
        }
        for(int i = 0 ; i < (PoleHeight - 2); i ++){
            obj.image = 3;
            obj.x = x + 0.5 * width;
            obj.y = y + height * 0.5 + ( i + 1) * (height);
            crd.x = obj.x; crd.y = obj.y;
            leftCrdV.push_back(crd);
            ObjManager::CreateObj(obj, id);
            ObjManager::AddToGrid(id, false);
            this->SaveObj(id);

            obj.image = 5;
            obj.x = x + (width) * (PoleWidth - 1)  + 0.5 * width;
            obj.y = y + .5 * height + (i + 1) * (height);
            crd.x = obj.x; crd.y = obj.y;
            rightCrdV.push_back(crd);
            ObjManager::CreateObj(obj, id);
            ObjManager::AddToGrid(id, false);
            this->SaveObj(id);
        }
        r = (Rect*)Root::PutEventToQueue(sizeof(Rect), SE_FIELDPARAM, STO_CHEKERS);
        r->left = x;
        r->right = x + PoleWidth * width;
        r->top = y;
        r->bottom = y + PoleHeight * height;
        fieldRect = *r;
        break;
    case SE_DELETEFIELD:
        while(this->GetVolume()){
            ObjManager::DeleteObj(this->GetObj(0));
            this->DeleteObj(0);
        }
        break;
    case SE_FIELD_SHINE_LEFT:
        CreateShineField(0);
        break;
    case SE_FIELD_SHINE_RIGHT:
        CreateShineField(1);
        break;
    case SE_FIELD_SHINE_CLOSE:{
        int i = 0/*(gridWidth * 2 +  2 * (gridHeight - 2))*/;
        while( i < (int)this->GetVolume()){
            ObjManager::GetObj(this->GetObj(i), obj);
            if((obj.tileId == ID_BMP_CELL_SHINE1) ||
                    (obj.tileId == ID_BMP_CELL_SHINE2) ||
                    (obj.tileId == ID_BMP_CELL_SHINE3)){
                ObjManager::DeleteObj(this->GetObj(i));
                this->DeleteObj(i);
            }
            else
                i++;
        }
        }break;
    case ME_TIMER:
        if(*((int*)data) != TIMER_ANIM)
            return;
        for(int i = 0/*(gridWidth * 2 +  2 * (gridHeight - 2))*/; i < (int)this->GetVolume(); i++ ){
            ObjManager::GetObj(this->GetObj(i), obj);
            bool change = true;
            switch(obj.tileId){
            case ID_BMP_CELL_SHINE1:
                obj.tileId = ID_BMP_CELL_SHINE2;
                break;
            case ID_BMP_CELL_SHINE2:
                obj.tileId = ID_BMP_CELL_SHINE3;
                break;
            case ID_BMP_CELL_SHINE3:
                obj.tileId = ID_BMP_CELL_SHINE1;
                break;
            default:
                change = false;
                break;
            }
            if(change)
                ObjManager::ChangeObj(this->GetObj(i), obj);
        }
    default:
        break;
    }
}
void Field::CreateShineField(int part){
    Object obj;
    IDn id;
    int left = 0;
    int right = gridWidth - 1;
    switch(part){
    default:
    case 0:
        right = gridWidth / 2 - 1;
        break;
    case 1:
        left = gridWidth / 2;
        break;
    }

    obj.subType = STO_FIELD;
    obj.sizeOfSubStr = 0;
    obj.levelOfDraw = 1;
    obj.SetTile(ID_BMP_CELL_SHINE1);
    for(int i = left; i <= right; i++){
        if(i == left)
            obj.image = 6;
        else if(i == right)
            obj.image = 8;
        else
            obj.image = 7;
        obj.x = topCrdV[i].x;
        obj.y = topCrdV[i].y;
        ObjManager::CreateObj(obj, id);
        ObjManager::AddToGrid(id, false);
        this->SaveObj(id);

        if(i == left)
            obj.image = 0;
        else if(i == right)
            obj.image = 2;
        else
            obj.image = 1;
        obj.x = bottomCrdV[i].x;
        obj.y = bottomCrdV[i].y;
        ObjManager::CreateObj(obj, id);
        ObjManager::AddToGrid(id, false);
        this->SaveObj(id);
    }
    int r_x = topCrdV[right].x;
    int l_x = topCrdV[left].x;
    for(int i = 0; i < (int)leftCrdV.size(); i++){
        obj.image = 3;
        obj.x = l_x;
        obj.y = leftCrdV[i].y;
        ObjManager::CreateObj(obj, id);
        ObjManager::AddToGrid(id, false);
        this->SaveObj(id);

        obj.image = 5;
        obj.x = r_x;
        obj.y = leftCrdV[i].y;
        ObjManager::CreateObj(obj, id);
        ObjManager::AddToGrid(id, false);
        this->SaveObj(id);
    }
}
