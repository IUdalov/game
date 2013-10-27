#ifndef OBJ_MANAGER_H
#define OBJ_MANAGER_H

//#include "dependences.h"
//#include "models.h"
//#include "object.h"
#include "geo.h"
//#include "root.h"
#include "main_window.h"


namespace INDIan{
    namespace ObjManager{
        struct GridParam{
            int widthGrid, heightGrid, widthCell, heightCell;
            Cell** lpGrid;
        };

        extern Coord Camera;

        bool IsActual(IDn ID);
        Rect GetActualWindRect();
        void ReBuildGrid(int _widthGrid,int _heightGrid,int _widthCell, int _heightCell,int sizeOfBg = 0);
        bool CreateObj(Object obj, IDn& id);
        bool DeleteObj(IDn id);
        bool GetObj(IDn id,Object& obj);
        bool ChangeObj(IDn id,Object obj);
        int GetObjStatus(IDn id);
        bool AddToGrid(IDn id,bool sendHit = false);
        bool DeleteFromGrid(IDn id);
        vector<IDn>* GetVObjByCrd(int _x, int _y);
        vector<IDn>* GetVObjByNum(int x, int y);
        void* GetBGByNum(int x, int y);
        bool GetGridStatus(void);
        bool GetGridParam(GridParam& gp);
        void ChangeCrdByCamera(int& x, int& y);
    }
}

#endif // OBJ_MANAGER_H
