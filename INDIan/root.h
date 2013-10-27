#ifndef ROOT_H
#define ROOT_H

#include "formuls.h"
#include "models.h"
#include "transport.h"

namespace INDIan {
    namespace Root {
        struct Message{
            void*			data;
            int	  to;
            int	mess;
            bool		dataFull;
        };
        enum{
            S_DOWN = 1,
            S_UP,
            S_WHEEL,
            S_DBLCLK
        };

        extern bool pause;
        extern bool drawMode;
        extern int numLevelDraw;

        bool Create(void);
        bool Draw(void);
        bool Timer();
        bool MouseUp(int mButton);
        bool MouseDown(int mButton);
        bool MouseMove(int x, int y);
        bool KeyDown(int key);
        bool KeyUp(int key);
        bool Destroy();
        int AddTimer(int timeSek);
        void* PutEventToQueue(int sizeOfData,int mess,int _to = 0);
        SMouse GetMouseStatus(void);
        void CloseApp();
        bool GetModelDrawMode(int);
        bool GetModelPauseMode(int);
        void AccessModel(Model*);
    }
}

#endif // ROOT_H
