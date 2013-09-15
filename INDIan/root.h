#ifndef ROOT_H
#define ROOT_H

#include "dependences.h"
#include "formuls.h"
#include "models.h"
#include "resources.h"

struct Message{
    void*			Data;
    unsigned int			  To;
    unsigned int			Mess;
    bool		DataFull;
};

enum{
    S_DOWN = 1,
    S_UP,
    S_WHEEL,
    S_DBLCLK
};

struct sMouse{
    short L,R,M;
    GLuint x,y;
};

class System_ROOT{
public:
    bool Pause, DrawMode;
    unsigned int NumLevelDraw;
private:
    sMouse Mouse;
    bool Keys[256];
    vector<Model_Objects*> DimOfModel;
    vector<Model_Objects*> DimOfSysModel;
    vector<SysTimer*> Timers;
    vector<Message> EQ;
private:
    void MakeQueueEvents(void);
    void TimerPlus();
public:
    System_ROOT();
    ~System_ROOT();
    bool Create(void);
    bool Draw(void);
    bool Timer();
    bool MouseUp(int mButton);
    bool MouseDown(int mButton);
    bool MouseMove(int x, int y);
    bool KeyDown(int key);
    bool KeyUp(int key);
    bool Destroy();
public:
    int AddTimer(GLuint timeSek);
    void* PutEventToQueue(int SizeOfData,unsigned int mess,unsigned int _To = 0);
    bool GetKeyStatus(short n);
    sMouse GetMouseStatus(void);
    void CloseApp();
    friend class Obj_Manager;
};

#endif // ROOT_H
