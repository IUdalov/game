#include "root.h"

extern QGLWidget* wndClass;

namespace INDIan{
    namespace Root{
        bool pause = false, drawMode = false;
        int numLevelDraw = 0;

        SMouse mouse;
        vector<Model*> dimOfModel;
        vector<Model*> dimOfSysModel;
        vector<SysTimer*> timers;
        vector<Message> messageQueue;

        void MakeQueueEvents(void);
        void TimerPlus();
        Model* FindModel(int type){
            for(int i = 0; i < (int)dimOfModel.size(); i++){
                if( ((int)dimOfModel[i]->GetSubType()) == type)
                    return dimOfModel[i];
            }
            return NULL;
        }

        void MakeQueueEvents(void){
            int k = 0;
            bool next = false;
            while((messageQueue.size()) && (k < (int)messageQueue.size())){
                if(messageQueue[k].to){
                    for(int i = 0; i < (int)dimOfModel.size(); i++){
                        if(dimOfModel[i]->GetSubType() == messageQueue[k].to){
                            if(pause){
                                if(dimOfModel[i]->notPaused){
                                    dimOfModel[i]->EventsHandler(messageQueue[k].mess,messageQueue[k].data);
                                }
                                else{
                                    k++;
                                    next = true;
                                    break;
                                }
                            }
                            else{
                                dimOfModel[i]->EventsHandler(messageQueue[k].mess,messageQueue[k].data);
                            }
                        }
                    }
                    if(next)
                        continue;
                }
                else{
                    for(int i = 0; i < (int)dimOfModel.size(); i++){
                        if(pause){
                            if(dimOfModel[i]->notPaused)
                                dimOfModel[i]->EventsHandler(messageQueue[k].mess,messageQueue[k].data);
                        }
                        else
                            dimOfModel[i]->EventsHandler(messageQueue[k].mess,messageQueue[k].data);
                    }
                    for(int i = 0; i < (int)dimOfSysModel.size(); i++){
                            dimOfSysModel[i]->EventsHandler(messageQueue[k].mess,messageQueue[k].data);
                    }
                }
                if(messageQueue[k].dataFull)
                    free(messageQueue[k].data);
                messageQueue.erase(messageQueue.begin() + k);
            }
        }
        void TimerPlus(){
            int Num;
            int* get = new int;
            for(int i = 0; i < (int)timers.size(); i++){
                timers[i]->CurTime++;
                if(timers[i]->CurTime >= timers[i]->MaxTime){
                    Num = timers[i]->MaxTime;
                    timers[i]->CurTime = 0;
                    for(int i = 0; i < (int)dimOfModel.size(); i++){
                        if(pause&&!dimOfModel[i]->notPaused)
                            continue;
                        *get = (int)Num;
                        dimOfModel[i]->EventsHandler(ME_TIMER, get);
                    }
                    for(int i = 0; i < (int)dimOfSysModel.size(); i++){
                        *get = (int)Num;
                        dimOfSysModel[i]->EventsHandler(ME_TIMER, get);
                    }
                }
            }
            delete get;
            MakeQueueEvents();
        }
        bool Create(void){
            srand((unsigned)time(0));
            QDebug debug(QtDebugMsg);
            debug<<"-----------------------------------------------------";

            for(int i = 0; i < (int)dimOfSysModel.size(); i++)
                dimOfSysModel[i]->EventsHandler(ME_CREATE, NULL);

            for(int i = 0; i < (int)dimOfModel.size(); i++)
                dimOfModel[i]->EventsHandler(ME_CREATE, NULL);

            return true;
        }
        bool Draw(void){
            int *nl;
            nl = new int;
            for(int i = 0; i < (int)numLevelDraw; i++){
                for(int k = 0; k < (int)dimOfSysModel.size(); k++){
                    *nl = i;
                    dimOfSysModel[k]->EventsHandler(ME_DRAW, nl);
                }
                for(int j = 0; j < (int)dimOfModel.size(); j++){
                    *nl = i;
                    if((dimOfModel[j]->onlyDraw && drawMode) || (!drawMode))
                        dimOfModel[j]->EventsHandler(ME_DRAW, nl);
                }
            }
            delete nl;
            return true;
        }
        bool Timer(){
            TimerPlus();
            return true;
        }
        bool MouseUp(int mButton){
               switch(mButton){
            case Qt::LeftButton:
                mouse.L = S_UP;
                goto MouseClick;
            case Qt::RightButton:
                mouse.R = S_UP;
                goto MouseClick;
            case Qt::MiddleButton:
                mouse.M = S_UP;
                goto MouseClick;
            }
        MouseClick:
                int TypeEvent =  ME_MOUSECLICK;
                for(int i = 0; i < (int)dimOfModel.size(); i++){
                    if((dimOfModel[i]->notPaused && pause) || (!pause))
                        dimOfModel[i]->EventsHandler(TypeEvent, NULL);
                }
                for(int k = 0; k < (int)dimOfSysModel.size(); k++){
                    dimOfSysModel[k]->EventsHandler(TypeEvent, NULL);
                }
                mouse.L = mouse.R = mouse.M = 0;
                return true;

        }
        bool MouseDown(int mButton){
            switch(mButton){
            case Qt::LeftButton:
                mouse.L = S_DOWN;
                goto MouseClick;
            case Qt::RightButton:
                mouse.R = S_DOWN;
                goto MouseClick;
            case Qt::MiddleButton:
                mouse.M = S_DOWN;
                goto MouseClick;
            }
        MouseClick:
                int TypeEvent =  ME_MOUSECLICK;
                for(int i = 0; i < (int)dimOfModel.size(); i++){
                    if((dimOfModel[i]->notPaused && pause) || (!pause))
                        dimOfModel[i]->EventsHandler(TypeEvent, NULL);
                }
                for(int k = 0; k < (int)dimOfSysModel.size(); k++){
                    dimOfSysModel[k]->EventsHandler(TypeEvent, NULL);
                }
                mouse.L = mouse.R = mouse.M = 0;
                return true;
        }
        bool MouseMove(int x, int y){
            mouse.x = x;
            mouse.y = y;
            for(int i = 0; i < (int)dimOfModel.size(); i++){
                if((dimOfModel[i]->notPaused && pause) || (!pause))
                    dimOfModel[i]->EventsHandler(ME_MOUSEMOVE, NULL);
            }
            for(int k = 0; k < (int)dimOfSysModel.size(); k++){
                dimOfSysModel[k]->EventsHandler(ME_MOUSEMOVE, NULL);
            }
            return true;
        }
        bool KeyDown(int key){
            int num;
            for(int i = 0; i < (int)dimOfModel.size(); i++){
                num = key;
                if((dimOfModel[i]->notPaused && pause) || (!pause))
                    dimOfModel[i]->EventsHandler(ME_KEYDOWN, &num);
            }
            for(int k = 0; k < (int)dimOfSysModel.size(); k++){
                num = key;
                dimOfSysModel[k]->EventsHandler(ME_KEYDOWN, &num);
            }
            return true;
        }
        bool KeyUp(int key){
            int num;
            for(int i = 0; i < (int)dimOfModel.size(); i++){
                num = key;
                if((dimOfModel[i]->notPaused && pause) || (!pause))
                    dimOfModel[i]->EventsHandler(ME_KEYUP, &num);
            }
            for(int k = 0; k < (int)dimOfSysModel.size(); k++){
                num = key;
                dimOfSysModel[k]->EventsHandler(ME_KEYUP, &num);
            }
            return true;
        }
        bool Destroy(){
            int TypeEvent =  ME_DESTROY;
            for(int i = 0; i < (int)dimOfModel.size(); i++)
                    dimOfModel[i]->EventsHandler(TypeEvent, NULL);
            for(int i = 0; i < (int)dimOfSysModel.size(); i++)
                    dimOfSysModel[i]->EventsHandler(TypeEvent, NULL);
            return true;
        }
        int AddTimer(int timeSek){
            if(timeSek <= 0)
                return -1;
            for(int i = 0; i < (int)timers.size(); i++)
                if(timeSek == (int)timers[i]->MaxTime)
                    return -2;
            SysTimer* ntm = new SysTimer;
            ntm->CurTime = 0;
            ntm->MaxTime = timeSek;
            timers.push_back(ntm);
            return timers.size() - 1;
        }
        void* PutEventToQueue(int sizeOfData,int mess,int _to){
            if(!mess)
                return NULL;
            Message M;

            M.to = _to;
            M.mess = mess;
            if(sizeOfData){
                M.dataFull = true;
                M.data = malloc(sizeOfData);
            }
            else{
                M.dataFull = false;
                M.data = NULL;
            }
            messageQueue.push_back(M);
            return M.data;
        }
        SMouse GetMouseStatus(void){
            return mouse;
        }
        void CloseApp(){
            exit(0);
        }
        void AccessModel(Model* model){
            if(model->GetSubType() == 0)
                dimOfSysModel.push_back(model);
            else
                dimOfModel.push_back(model);
        }
        bool GetModelDrawMode(int type){
            Model* model = FindModel(type);
            if(model)
                return model->onlyDraw;
            else
                return false;
        }
        bool GetModelPauseMode(int type){
            Model* model = FindModel(type);
            if(model)
                return model->notPaused;
            else
                return false;
        }
    }
}



