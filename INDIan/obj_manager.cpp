#include "obj_manager.h"

namespace INDIan{
    namespace ObjManager{
        enum ObjStatus{
            OS_NORMAL = 1,
            OS_DELETE,
            OS_NOTACTUAL
        };
        bool find_in_vector(vector<IDn>& vector, IDn elem);
        struct ObjRoom{
            Object obj;
            Object oldObj;
            int status;
            bool wasDraw;
            int dateBorn;
        };

        Coord camera = {0, 0};

        bool stageDraw = false;
        vector<ObjRoom*> dimOfObj;
        vector<int> dimOfDel;
        Cell** grid = NULL;
        bool gridBgIsFull = false;
        bool newDraw = false;
        int curDate = 0;
        int widthGrid = 0, heightGrid = 0, widthCell = 0, heightCell = 0;

        void DrawByGrid(int numLev){
            if(!grid)
                return;

            if(newDraw)
                stageDraw =! stageDraw;

            int left = camera.x / ((int)widthCell);
            int right = (camera.y + (int)GLWindow::GetScreenWidth()) / ((int)widthCell);
            int top = camera.y / ((int)heightCell);
            int bottom = (camera.y + (int)GLWindow::GetScreenHeight()) / ((int)heightCell);

            right = right >= (int)widthGrid ? (int)widthGrid - 1 : right;
            bottom = bottom>=(int)heightGrid ? (int)heightGrid - 1 : bottom;
            left = left < 0 ? 0 : left;
            top = top < 0 ? 0 : top;
            if((left > (int)widthGrid) || (top > (int)heightGrid) || (bottom < 0) || (right < 0))
                return;

            for(int j = top; j <= bottom; j++){
                for(int i = left; i <= right; i++){
                    if(newDraw)
                        grid[i][j].curNum=0;
                    int* lpNum = &(grid[i][j].curNum);
                    while(( (*lpNum) < (int)grid[i][j].objects.size() ) &&
                            (dimOfObj[ObjManager::grid[i][j].objects[*lpNum].id]->obj.levelOfDraw == (int)numLev))
                    {
                        if(!(dimOfObj[grid[i][j].objects[*lpNum].id]->status == OS_DELETE)){
                            if(!(dimOfObj[grid[i][j].objects[*lpNum].id]->wasDraw == stageDraw)){
                                if(!( (Root::drawMode) && (! Root::GetModelDrawMode(ObjManager::dimOfObj[grid[i][j].objects[*lpNum].id]->obj.subType)))){
                                    dimOfObj[grid[i][j].objects[*lpNum].id]->obj.DrawWithMove(-(camera.x),-(camera.y));
                                    dimOfObj[grid[i][j].objects[*lpNum].id]->wasDraw = stageDraw;
                                }
                            }
                        }
                        (*lpNum) += 1;
                    }

                }
            }
            newDraw = false;
        }
        bool isActual(IDn id){
            if( id.id >= (int)dimOfObj.size())
                return false;
            if ((dimOfObj[id.id]->status == OS_DELETE) || (dimOfObj[id.id]->dateBorn != id.dateBorn) )
                return false;
            return true;
        }
        Rect GetActualWindRect(){
            Rect    rect;
            rect.left = (int)(camera.x / widthCell);
            rect.right = (int)((camera.x + GLWindow::GetScreenWidth()) / widthCell) + 1;
            rect.top = (int)(camera.y / heightCell);
            rect.bottom = (int)((camera.y + GLWindow::GetScreenHeight()) / heightCell) + 1;

            rect.right = MIN(rect.right, widthGrid - 1);
            rect.bottom = MIN(rect.bottom, heightGrid - 1);
            rect.left = MAX(rect.left, 0);
            rect.top = MAX(rect.top, 0);
            return rect;
        }
        void ReBuildGrid(int _widthGrid,int _heightGrid,int _widthCell, int _heightCell,int sizeOfBg){
            if(_widthGrid == 0 || _heightGrid == 0 || _widthCell == 0 || _heightCell == 0)
                return;

            if(grid){
                for(int i = 0; i < (int)widthGrid; i++){
                    for(int j = 0; j < (int)heightGrid; j++){
                        grid[i][j].objects.clear();
                        if(gridBgIsFull){
                            delete[] (char*)grid[i][j].backGround;
                            grid[i][j].backGround = NULL;
                        }
                    }
                }
                for(int i = 0; i < (int)widthGrid; i++)
                    delete grid[i];
                delete grid;
                grid = NULL;
            }
            widthGrid = _widthGrid;
            heightGrid = _heightGrid;
            widthCell = _widthCell;
            heightCell = _heightCell;
            if(sizeOfBg)
                gridBgIsFull = true;
            else
                gridBgIsFull = false;

            grid = new Cell*[widthGrid];

            for(int i = 0; i < widthGrid; i++)
                grid[i] = new Cell[heightGrid];

            for(int i = 0; i < widthGrid; i++){
                for(int j = 0; j < heightGrid; j++){
                    if(sizeOfBg){
                        char *lp = new char[sizeOfBg];
                        grid[i][j].backGround = (void*)lp;
                    }
                    else{
                        grid[i][j].backGround = NULL;
                    }
                }
            }
        }
        void Destroy(){
            if(grid){
                for(int i = 0; i < widthGrid; i++){
                    for(int j = 0; j < heightGrid; j++){
                        grid[i][j].objects.clear();
                        if(gridBgIsFull){
                            delete[] (char*)grid[i][j].backGround;
                            grid[i][j].backGround = NULL;
                        }
                    }
                }
                for(int i = 0; i < widthGrid; i++)
                    delete [](grid[i]);
                delete []grid;
                grid = NULL;

            }
            for(int i = 0; i < (int)dimOfObj.size(); i++){
                if( (dimOfObj[i]->obj.sizeOfSubStr) && (dimOfObj[i]->status == OS_NORMAL))
                    free(dimOfObj[i]->obj.subStr);
                delete dimOfObj[i];
            }
        }
        bool CreateObj(Object obj, IDn& _id){
            IDn newID;
            ObjRoom* Room = new ObjRoom;
            if(obj.sizeOfSubStr)
                obj.subStr = malloc(obj.sizeOfSubStr);
            Room->obj = Room->oldObj = obj;
            Room->status = OS_NORMAL;
            Room->wasDraw = stageDraw;
            Room->dateBorn = newID.dateBorn = curDate;
            newID.id = dimOfObj.size();
            curDate++;
            dimOfObj.push_back(Room);
            _id = newID;
            return true;
        }
        bool DeleteObj(IDn id){
            if(!isActual(id))
                return false;

            DeleteFromGrid(id);
            dimOfDel.push_back(id.id);

            if(dimOfObj[id.id]->obj.sizeOfSubStr){
                free(dimOfObj[id.id]->obj.subStr);
            }
            dimOfObj[id.id]->status = OS_DELETE;
            return true;
        }
        bool GetObj(IDn id,Object& Obj){
            if(!isActual(id))
                return false;

            Obj = dimOfObj[id.id]->obj;
            return true;
        }
        bool ChangeObj(IDn id,Object Obj){
            if(!isActual(id))
                return false;
            dimOfObj[id.id]->obj = Obj;
            return true;
        }
        int GetObjStatus(IDn id){
            if(!isActual(id))
                return OS_NOTACTUAL;
            return dimOfObj[id.id]->status;
        }
        bool AddToGrid(IDn id,bool SendHit){
            if(!isActual(id))
                return false;
            if(!grid)
                return false;

            Object obj = dimOfObj[id.id]->obj;

            PntRect rect = obj.GetPntRect();

            int left = (MinXPntRect(rect) / (int)widthCell);
            int right = (MaxXPntRect(rect) / (int)widthCell);
            int top = (MinYPntRect(rect) / (int)heightCell);
            int bottom = (MaxYPntRect(rect) / (int)heightCell);

            right = right >= (int)widthGrid ? (int)widthGrid-1 : (int)right;
            bottom = bottom >= (int)heightGrid ? (int)heightGrid-1 : (int)bottom;
            left = left < 0 ? 0 : left;
            top = top < 0 ? 0 : top;
            if( (left > (int)widthGrid) || (top > (int)heightGrid) || (bottom < 0) || (right < 0))
                return false;

            vector<IDn> v_id;
            vector<Object> v_obj;

            for( int i = left; i <= right; i++){
                for( int j = top; j <= bottom; j++){
                    int NewNum = grid[i][j].objects.size();
                    int LevDr = obj.levelOfDraw;
                    bool check_level_draw = false;
                    for( int k = 0; k < (int)grid[i][j].objects.size(); k++){
                        IDn ID2 = grid[i][j].objects[k];
                        Object obj2 = dimOfObj[ID2.id]->obj;

                        if(SendHit){
                            if(!find_in_vector(v_id, ID2)){
                                v_id.push_back(ID2);
                                v_obj.push_back(obj2);
                            }
                        }
                        if( (!check_level_draw) && (obj2.levelOfDraw > LevDr) ){
                            check_level_draw = true;
                            NewNum = k;
                        }
                    }
                    grid[i][j].objects.insert(grid[i][j].objects.begin() + NewNum,id);
                }
            }
            GeoScaner geo_scan;
            Object obj_for_geo = obj;
            Object obj2;
            IDn ID2;
            geo_scan.init(GST_BREP_BREP, v_obj, &obj_for_geo, sizeof(Object));
            GEO_SCAN_ANS gs_answer;
            while( GSA_CANCEL != (gs_answer = geo_scan.scan()) ){
                if( gs_answer == GSA_OK ){
                    obj2 = geo_scan.GetCurrElem();
                    ID2 = v_id[geo_scan.GetCurrElemNum()];

                    OEDClash* data = (OEDClash*)Root::PutEventToQueue(sizeof(OEDClash), OE_CLASH, obj.subType);
                    data->idDest = id;
                    data->idSrc = ID2;
                    if(obj.subType != obj2.subType){
                        OEDClash* data = (OEDClash*)Root::PutEventToQueue(sizeof(OEDClash), OE_CLASH, obj2.subType);
                        data->idDest = ID2;
                        data->idSrc = id;
                    }
                }
            }
            return true;
        }
        bool DeleteFromGrid(IDn id){
            if(!isActual(id))
                return false;
            if(!grid)
                return false;

            Object* obj = &(dimOfObj[id.id]->obj);

            PntRect rect=obj->GetPntRect();

            int left = (MinXPntRect(rect) / (int)widthCell);
            int right = (MaxXPntRect(rect) / (int)widthCell);
            int top = (MinYPntRect(rect) / (int)heightCell);
            int bottom = (MaxYPntRect(rect) / (int)heightCell);

            right = right >= (int)widthGrid ? (int)widthGrid-1 : right;
            bottom = bottom >= (int)heightGrid ? (int)heightGrid-1 : bottom;
            left = left < 0 ? 0 : left;
            top = top < 0 ? 0 : top;
            if( (left > (int)widthGrid) || (top > (int)heightGrid) || (bottom < 0) || (right < 0))
                return false;


            for( int i = left; i <= right; i++){
                for( int j = top; j <= bottom; j++){
                    bool next = false;
                    for( int k = 0; k < (int)grid[i][j].objects.size(); k++){
                        if( (grid[i][j].objects[k].id == id.id) && (grid[i][j].objects[k].dateBorn == id.dateBorn)){
                            grid[i][j].objects.erase(grid[i][j].objects.begin()+k);
                            next = true;
                        }
                        if(next)
                            break;
                    }
                }
            }
            return true;
        }
        vector<IDn>* GetVObjByCrd(int _x, int _y){
            int x = (int)(_x / widthCell);
            int y = (int)(_y / heightCell);
            if( (x >= widthGrid) || (y >= heightGrid))
                return NULL;
            return &(grid[x][y].objects);
        }
        vector<IDn>* GetVObjByNum(int x, int y){
            if( (x >= widthGrid) || (y >= heightGrid))
                return NULL;
            return &(grid[x][y].objects);
        }
        void* GetBGByNum(int x, int y){
            if( (x >= widthGrid) || (y >= heightGrid))
                return NULL;
            return grid[x][y].backGround;
        }
        bool GetGridStatus(void){
            if(grid)
                return true;
            return false;
        }
        bool GetGridParam(GridParam& gp){
            if(!grid)
                return false;
            gp.lpGrid = grid;
            gp.widthGrid = widthGrid;
            gp.heightGrid = heightGrid;
            gp.widthCell = widthCell;
            gp.heightCell = heightCell;
            return true;
        }
        void ChangeCrdByCamera(int& x, int& y){
            x += camera.x;
            y += camera.y;
        }
        void HandleMouseEvents(long mess){
            SMouse ms = Root::GetMouseStatus();
            vector<IDn>* vCell = GetVObjByCrd(ms.x, ms.y);
            vector<Object> vObj;
            vector<IDn> vId;
            Object obj;
            if((!vCell) || (!vCell->size()))
                return;

            for(int i = (int)vCell->size() - 1; i >= 0; i--)
                if(GetObj((*vCell)[i], obj)){
                    vObj.push_back(obj);
                    vId.push_back((*vCell)[i]);
                }

            DCoord mouseCrd = {(double)ms.x, (double)ms.y};
            GeoScaner geo_scan;
            IDn id;
            GEO_SCAN_ANS gs_answer;
            geo_scan.init(GST_BREP_PNT, vObj, &mouseCrd, sizeof(DCoord));
            while( GSA_CANCEL != (gs_answer = geo_scan.scan()) ){
                if( gs_answer == GSA_OK ){
                    obj = geo_scan.GetCurrElem();
                    id = vId[geo_scan.GetCurrElemNum()];

                    OEDMouse* data = (OEDMouse*)Root::PutEventToQueue(sizeof(OEDMouse), mess, obj.subType);
                    data->idObj = id;
                    data->mouse = ms;
                }
            }

        }

        class ObjectsManagerModel : Model{
        public:
            ObjectsManagerModel() : Model(0,0){
                Root::AccessModel(this);
            }
            void EventsHandler(int mess,void* data){
                switch(mess){
                    case ME_DRAW:
                        if(*((int*)data) == 0)
                            ObjManager::newDraw = true;
                        ObjManager::DrawByGrid(*((int*)data));
                        break;
                    case ME_MOUSECLICK:
                        ObjManager::HandleMouseEvents(OE_MOUSECLICK);
                        break;
                    case ME_MOUSEMOVE:
                        ObjManager::HandleMouseEvents(OE_MOUSEMOVE);
                        break;
                    case ME_DESTROY:
                        ObjManager::Destroy();
                        break;
                    default:
                        break;
                }
            }
        }ObjManModel;

        bool find_in_vector(vector<IDn>& vect, IDn elem){
            vector<IDn>::iterator iter;
            for(iter = vect.begin(); iter != vect.end(); iter++){
                if(*iter == elem){
                    return true;
                }
            }
            return false;
        }
    }
}

