#ifndef OBJ_MANAGER_H
#define OBJ_MANAGER_H

#include "dependences.h"
#include "formuls.h"
#include "transport.h"
//#include "models.h"

namespace INDIan{
    class Object;

    namespace ObjManager{
        struct GridParam{
            int widthGrid, heightGrid, widthCell, heightCell;
            Cell** lpGrid;
        };
        enum ObjStatus{
            OS_DELETE = 0x00000000,
            OS_ACTUAL = 0x00000001,
            OS_INGRID = 0x00000010
        };

        extern Coord Camera;

        bool IsActual(IDn id);
        Rect GetActualWindRect();
        void ReBuildGrid(int _widthGrid,int _heightGrid,int _widthCell, int _heightCell,int sizeOfBg = 0);
        bool CreateObj(Object obj, IDn& id);
        bool DeleteObj(IDn id);
        void DeleteObjs(const vector<IDn>& vId);
        bool GetObj(IDn id,Object& obj);
        bool ChangeObj(IDn id,Object obj);
        int GetObjStatus(IDn id);
        bool AddToGrid(IDn id,bool sendHit = false);
        bool DeleteFromGrid(IDn id);
        void AddToGrid(vector<IDn> v_id,bool sendHit = false);
        void DeleteFromGrid(vector<IDn> v_id);
        vector<IDn>* GetVObjByCrd(int _x, int _y);
        vector<IDn>* GetVObjByNum(int x, int y);
        void* GetBGByNum(int x, int y);
        bool GetGridStatus(void);
        bool GetGridParam(GridParam& gp);
        void ChangeCrdByCamera(int& x, int& y);
        void Init();
    }
}

#endif // OBJ_MANAGER_H
