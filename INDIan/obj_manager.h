#ifndef OBJ_MANAGER_H
#define OBJ_MANAGER_H

#include "dependences.h"
#include "root.h"
#include "models.h"
#include "object.h"


#define OS_NORMAL	 1
#define OS_DELETE	 2
#define OS_NOTACTUAL 3

struct GridParam{
    unsigned int Width_Grid,Height_Grid,Width_Cell,Height_Cell;
    Cell** lpGrid;
};
struct ObjRoom{
    CObj		Obj;
    CObj	 OldObj;
    unsigned int	 Status;
    bool	WasDraw;
    unsigned int  DateBorn;
};

class Obj_Manager{
public:
    COORD Camera;
private:
    bool StageDraw;
    vector<ObjRoom*> DimOfObj;
    vector<unsigned int>	 DimOfDel;
    Cell** Grid;
    bool GridBgIsFull;
    bool NewDraw;
    unsigned int CurDate;
    unsigned int Width_Grid, Height_Grid, Width_Cell, Height_Cell;
private:
    void DrawByGrid(int NumLev);
public:
    bool isActual(IDn ID);
    RECT GetActualWindRect();
    void ReBuildGrid(unsigned int _Width_Grid,unsigned int _Height_Grid,unsigned int _Width_Cell, unsigned int _Height_Cell,int SizeOfBg = 0);
    Obj_Manager();
    ~Obj_Manager();
    bool CreateObj(CObj obj, IDn& _ID);
    bool DeleteObj(IDn ID);
    bool GetObj(IDn ID,CObj& Obj);
    bool ChangeObj(IDn ID,CObj Obj);
    int GetObjStatus(IDn ID);
    bool AddToGrid(IDn ID,bool SendHit = false);
    bool DeleteFromGrid(IDn ID);
    vector<IDn>* GetVObjByCrd(unsigned int _x, unsigned int _y);
    vector<IDn>* GetVObjByNum(unsigned int x,unsigned int y);
    void* GetBGByNum(unsigned int x,unsigned int y);
    bool GetGridStatus(void);
    bool GetGridParam(GridParam& gp);
    void ChangeCrdByCamera(unsigned int& x, unsigned int& y);
    friend class cObjectsManager;
};


class cObjectsManager:Model_Objects{
public:
    cObjectsManager();
    virtual void EventsHandler(unsigned int mess,void* data);
};



#endif // OBJ_MANAGER_H
