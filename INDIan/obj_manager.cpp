#include "obj_manager.h"

extern System_ROOT Root;
extern int ScreenWidth;
extern int ScreenHeight;
extern cResources Resources;
extern vector<Model_Objects*> DimOfModels;

Obj_Manager ObjManager;
cObjectsManager ObjectsManager;

void Obj_Manager::DrawByGrid(int NumLev){
    if(!Grid)
        return;

    if(NewDraw)
        StageDraw=!StageDraw;

    int left = Camera.x/((int)Width_Cell);
    int right = (Camera.y+(int)Root.GetScreenWidth())/((int)Width_Cell);
    int top = Camera.y/((int)Height_Cell);
    int bottom = (Camera.y+(int)Root.GetScreenHeight())/((int)Height_Cell);

    right=right>=(int)Width_Grid?(int)Width_Grid-1:right;
    bottom=bottom>=(int)Height_Grid?(int)Height_Grid-1:bottom;
    left=left<0?0:left;
    top=top<0?0:top;
    if(left>(int)Width_Grid||top>(int)Height_Grid||bottom<0||right<0)
        return;

    for(unsigned int j = (unsigned int)top; j <= (unsigned int)bottom; j++){
        for(unsigned int i = (unsigned int)left; i <= (unsigned int)right; i++){
            if(NewDraw)
                Grid[i][j].CurNum=0;
            unsigned int* lpNum=&(Grid[i][j].CurNum);
            while(((*lpNum)<Grid[i][j].Objects.size())&&
                    (DimOfObj[ObjManager.Grid[i][j].Objects[*lpNum].ID]->Obj.LevelOfDraw==(unsigned int)NumLev))
            {
                if(!(DimOfObj[Grid[i][j].Objects[*lpNum].ID]->Status==OS_DELETE)){
                    if(!(DimOfObj[Grid[i][j].Objects[*lpNum].ID]->WasDraw==StageDraw)){
                        if(!(Root.DrawMode&&!ObjManager.DimOfObj[Grid[i][j].Objects[*lpNum].ID]->Obj.GetLpModel()->OnlyDraw)){
                            DimOfObj[Grid[i][j].Objects[*lpNum].ID]->Obj.DrawWithMove(-(Camera.x),-(Camera.y));
                            DimOfObj[Grid[i][j].Objects[*lpNum].ID]->WasDraw=StageDraw;
                        }
                    }
                }
                (*lpNum)+=1;
            }

        }
    }
    NewDraw=false;
}
bool Obj_Manager::isActual(IDn ID){
    if( ID.ID >= DimOfObj.size())
        return false;
    if ((DimOfObj[ID.ID]->Status == OS_DELETE) || (DimOfObj[ID.ID]->DateBorn != ID.DateBorn) )
        return false;
    return true;
}
Rect Obj_Manager::GetActualWindRect(){
    Rect    rect;
    rect.left=(unsigned int)(Camera.x/Width_Cell);
    rect.right=(unsigned int)((Camera.x+Root.GetScreenWidth())/Width_Cell) + 1;
    rect.top=(unsigned int)(Camera.y/Height_Cell);
    rect.bottom=(unsigned int)((Camera.y+Root.GetScreenHeight())/Height_Cell) + 1;

    rect.right=MIN((unsigned)rect.right,Width_Grid-1);
    rect.bottom=MIN((unsigned)rect.bottom,Height_Grid-1);
    rect.left=MAX(rect.left,0);
    rect.top=MAX(rect.top,0);
    return rect;
}
void Obj_Manager::ReBuildGrid(unsigned int _Width_Grid,unsigned int _Height_Grid,unsigned int _Width_Cell, unsigned int _Height_Cell,int SizeOfBg){
    if(_Width_Grid==0||_Height_Grid==0||_Width_Cell==0||_Height_Cell==0)
        return;

    if(Grid){
        for(unsigned int i=0;i<Width_Grid;i++){
            for(unsigned int j=0;j<Height_Grid;j++){
                Grid[i][j].Objects.clear();
                if(GridBgIsFull){
                    delete[] (char*)Grid[i][j].BackGround;
                    Grid[i][j].BackGround = NULL;
                }
            }
        }
        for(unsigned int i=0;i<Width_Grid;i++)
            delete Grid[i];
        delete Grid;
        Grid = NULL;
    }
    Width_Grid = _Width_Grid;
    Height_Grid = _Height_Grid;
    Width_Cell = _Width_Cell;
    Height_Cell = _Height_Cell;
    if(SizeOfBg)
        GridBgIsFull = true;
    else
        GridBgIsFull = false;

    Grid = new Cell*[Width_Grid];

    for(unsigned int i=0;i<Width_Grid;i++)
        Grid[i]=new Cell[Height_Grid];

    for(unsigned int i=0;i<Width_Grid;i++){
        for(unsigned int j=0;j<Height_Grid;j++){
            if(SizeOfBg){
                char *lp = new char[SizeOfBg];
                Grid[i][j].BackGround = (void*)lp;
            }
            else{
                Grid[i][j].BackGround = NULL;
            }
        }
    }
}
Obj_Manager::Obj_Manager(){
    NewDraw=false;
    Grid=NULL;
    GridBgIsFull=false;
    StageDraw=false;
    CurDate=0;
    Width_Grid = Height_Grid =
        Width_Cell = Height_Cell = 0;
    Camera.x = Camera.y = 0;
}
Obj_Manager::~Obj_Manager(){
    if(Grid){
        for(unsigned int i=0;i<Width_Grid;i++){
            for(unsigned int j=0;j<Height_Grid;j++){
                Grid[i][j].Objects.clear();
                if(GridBgIsFull){
                    delete[] (char*)Grid[i][j].BackGround;
                    Grid[i][j].BackGround = NULL;
                }
            }
        }
        for(unsigned int i=0;i<Width_Grid;i++)
            delete [](Grid[i]);
        delete []Grid;
        Grid = NULL;

    }
    for(unsigned int i = 0; i < DimOfObj.size(); i++){
        if( (DimOfObj[i]->Obj.lpModel->SizeOfSubStr) && (DimOfObj[i]->Status == OS_NORMAL))
            free(DimOfObj[i]->Obj.GetSubStr());
        delete DimOfObj[i];
    }
}
bool Obj_Manager::CreateObj(CObj obj, IDn& _ID){
    if((!obj.lpModel)||(!obj.SubType))
        return false;
    IDn newID;
    ObjRoom* Room=new ObjRoom;
    if(obj.lpModel->SizeOfSubStr)
        obj.SubStr = malloc(obj.lpModel->SizeOfSubStr);
    Room->Obj=Room->OldObj=obj;
    Room->Status=OS_NORMAL;
    Room->WasDraw=StageDraw;
    Room->DateBorn=newID.DateBorn=CurDate;
    newID.ID=DimOfObj.size();
    CurDate++;
    DimOfObj.push_back(Room);
    obj.lpModel->Plus(newID);
    _ID = newID;
    return true;
}
bool Obj_Manager::DeleteObj(IDn ID){
    if(!isActual(ID))
        return false;

    DeleteFromGrid(ID);
    DimOfDel.push_back(ID.ID);

    if(DimOfObj[ID.ID]->Obj.lpModel->SizeOfSubStr){
        free(DimOfObj[ID.ID]->Obj.SubStr);
    }
    DimOfObj[ID.ID]->Obj.lpModel->DeleteObj(ID);
    DimOfObj[ID.ID]->Status=OS_DELETE;
    return true;
}
bool Obj_Manager::GetObj(IDn ID,CObj& Obj){
    if(!isActual(ID))
        return false;

    Obj = DimOfObj[ID.ID]->Obj;
    return true;
}
bool Obj_Manager::ChangeObj(IDn ID,CObj Obj){
    if(!isActual(ID))
        return false;
    DimOfObj[ID.ID]->Obj=Obj;
    return true;
}
int Obj_Manager::GetObjStatus(IDn ID){
    if(!isActual(ID))
        return OS_NOTACTUAL;
    return DimOfObj[ID.ID]->Status;
}
bool Obj_Manager::AddToGrid(IDn ID,bool SendHit){
    if(!isActual(ID))
        return false;
    if(!Grid)
        return false;

    CObj* obj=&(DimOfObj[ID.ID]->Obj);

    Model_Objects* MO=obj->lpModel;
    pntRect rect = obj->GetPntRect();

    int left = (MinXPntRect(rect) / (int)Width_Cell);
    int right = (MaxXPntRect(rect) / (int)Width_Cell);
    int top = (MinYPntRect(rect) / (int)Height_Cell);
    int bottom = (MaxYPntRect(rect) / (int)Height_Cell);

    right = right >= (int)Width_Grid ? (int)Width_Grid-1 : (int)right;
    bottom = bottom >= (int)Height_Grid ? (int)Height_Grid-1 : (int)bottom;
    left = left < 0 ? 0 : left;
    top = top < 0 ? 0 : top;
    if( (left > (int)Width_Grid) || (top > (int)Height_Grid) || (bottom < 0) || (right < 0))
        return false;

    Cell copy;

    for( int i = left; i <= right; i++){
        for( int j = top; j <= bottom; j++){
            if(SendHit){
                for( int k = 0; k < (int)Grid[i][j].Objects.size(); k++){
                    IDn ID2 = Grid[i][j].Objects[k];
                    CObj* obj2 = &(DimOfObj[ID2.ID]->Obj);
                    Model_Objects* MO2 = obj2->lpModel;

                    bool next = false;
                    for( int p=0;p < (int)copy.Objects.size(); p++){
                        if( (copy.Objects[p].ID == ID2.ID) && (copy.Objects[p].DateBorn == ID2.DateBorn))
                            next = true;
                        if(next)
                            break;
                    }
                    if(next)
                        continue;


                    copy.Objects.push_back(ID2);

                    IDn* data = (IDn*)Root.PutEventToQueue(sizeof(IDn)*2, ME_HITEVENT,MO->GetSubType());
                    *data = ID;
                    data++;
                    *data = ID2;
                    if(MO != MO2){
                        data = (IDn*)Root.PutEventToQueue(sizeof(IDn)*2, ME_HITEVENT,MO2->GetSubType());
                        data = &ID2;
                        data++;
                        data = &ID;
                    }
                }
            }
            unsigned int NewNum = Grid[i][j].Objects.size();
            unsigned int LevDr = DimOfObj[ID.ID]->Obj.LevelOfDraw;
            for( int k = 0; k < (int)Grid[i][j].Objects.size(); k++){
                if(DimOfObj[Grid[i][j].Objects[k].ID]->Obj.LevelOfDraw>LevDr){
                    NewNum = k;
                    break;
                }
            }
            Grid[i][j].Objects.insert(Grid[i][j].Objects.begin()+NewNum,ID);
        }
    }
    copy.Objects.clear();
    return true;
}
bool Obj_Manager::DeleteFromGrid(IDn ID){
    if(!isActual(ID))
        return false;
    if(!Grid)
        return false;

    CObj* obj=&(DimOfObj[ID.ID]->Obj);

    pntRect rect=obj->GetPntRect();

    int left = (MinXPntRect(rect) / (int)Width_Cell);
    int right = (MaxXPntRect(rect) / (int)Width_Cell);
    int top = (MinYPntRect(rect) / (int)Height_Cell);
    int bottom = (MaxYPntRect(rect) / (int)Height_Cell);

    right = right >= (int)Width_Grid ? (int)Width_Grid-1 : right;
    bottom = bottom >= (int)Height_Grid ? (int)Height_Grid-1 : bottom;
    left = left < 0 ? 0 : left;
    top = top < 0 ? 0 : top;
    if( (left > (int)Width_Grid) || (top > (int)Height_Grid) || (bottom < 0) || (right < 0))
        return false;


    for( int i = left; i <= right; i++){
        for( int j = top; j <= bottom; j++){
            bool next = false;
            for( int k = 0; k < (int)Grid[i][j].Objects.size(); k++){
                if( (Grid[i][j].Objects[k].ID == ID.ID) && (Grid[i][j].Objects[k].DateBorn == ID.DateBorn)){
                    Grid[i][j].Objects.erase(Grid[i][j].Objects.begin()+k);
                    next = true;
                }
                if(next)
                    break;
            }
        }
    }
    return true;
}
vector<IDn>* Obj_Manager::GetVObjByCrd(unsigned int _x, unsigned int _y){
    unsigned int x = (unsigned int)(_x / Width_Cell);
    unsigned int y = (unsigned int)(_y / Height_Cell);
    if( (x >= Width_Grid) || (y >= Height_Grid))
        return NULL;
    return &(Grid[x][y].Objects);
}
vector<IDn>* Obj_Manager::GetVObjByNum(unsigned int x,unsigned int y){
    if( (x >= Width_Grid) || (y >= Height_Grid))
        return NULL;
    return &(Grid[x][y].Objects);
}
void* Obj_Manager::GetBGByNum(unsigned int x,unsigned int y){
    if( (x >= Width_Grid) || (y >= Height_Grid))
        return NULL;
    return Grid[x][y].BackGround;
}
bool Obj_Manager::GetGridStatus(void){
    if(Grid)
        return true;
    return false;
}
bool Obj_Manager::GetGridParam(GridParam& gp){
    if(!Grid)
        return false;
    gp.lpGrid = Grid;
    gp.Width_Grid=Width_Grid;
    gp.Height_Grid=Height_Grid;
    gp.Width_Cell=Width_Cell;
    gp.Height_Cell=Height_Cell;
    return true;
}
void Obj_Manager::ChangeCrdByCamera(unsigned int& x, unsigned int& y){
    x += Camera.x;
    y += Camera.y;
}


cObjectsManager::cObjectsManager():Model_Objects(0,0){
}
void cObjectsManager::EventsHandler(unsigned int mess,void* data){
    switch(mess){
        case ME_DRAW:
            if(*((unsigned int*)data) == 0)
                ObjManager.NewDraw = true;
            ObjManager.DrawByGrid(*((unsigned int*)data));
            break;
        default:
            break;
    }
}


