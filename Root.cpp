#include "Root.h"
#include "Models.h"

System_ROOT Root;

extern vector<Model_Objects*> DimOfModels;
extern cResources Resources;

void System_ROOT::MakeQueueEvents(void){
    GLuint k=0;
    bool next = false;
    while(EQ.size()&&k<EQ.size()){
        if(EQ[k].To){
            for(GLuint i=0;i<DimOfModel.size();i++){
                if(DimOfModel[i]->GetSubType()==EQ[k].To){
                    if(Pause){
                        if(DimOfModel[i]->NotPaused){
                            DimOfModel[i]->EventsHandler(EQ[k].Mess,EQ[k].Data);
                        }
                        else{
                            k++;
                            next = true;
                            break;
                        }
                    }
                    else{
                        DimOfModel[i]->EventsHandler(EQ[k].Mess,EQ[k].Data);
                    }
                }
            }
            if(next)
                continue;
        }
        else{
            for(GLuint i=0;i<DimOfModel.size();i++){
                if(Pause){
                    if(DimOfModel[i]->NotPaused)
                        DimOfModel[i]->EventsHandler(EQ[k].Mess,EQ[k].Data);
                }
                else
                    DimOfModel[i]->EventsHandler(EQ[k].Mess,EQ[k].Data);
            }
            for(GLuint i=0;i<DimOfSysModel.size();i++){
                    DimOfSysModel[i]->EventsHandler(EQ[k].Mess,EQ[k].Data);
            }
        }
        if(EQ[k].DataFull)
            free(EQ[k].Data);
        EQ.erase(EQ.begin()+k);
    }
}
void System_ROOT::TimerPlus(){
    GLuint Num;
    GLuint* get = new GLuint;
    for(GLuint i=0;i<Timers.size();i++){
        Timers[i]->CurTime++;
        if(Timers[i]->CurTime>=Timers[i]->MaxTime){
            Num=Timers[i]->MaxTime;
            Timers[i]->CurTime=0;
            for(GLuint i=0;i<DimOfModel.size();i++){
                if(Pause&&!DimOfModel[i]->NotPaused)
                    continue;
                *get=(GLuint)Num;
                DimOfModel[i]->EventsHandler(ME_TIMER,get);
            }
            for(GLuint i=0;i<DimOfSysModel.size();i++){
                *get=(GLuint)Num;
                DimOfSysModel[i]->EventsHandler(ME_TIMER,get);
            }
        }
    }
    delete get;
    MakeQueueEvents();
}
System_ROOT::System_ROOT(){
    Pause = DrawMode = false;
    NumLevelDraw = 0;
    Mouse.L = Mouse.R = Mouse.M = S_UP;
    for(GLuint i=0;i<256;i++)
        Keys[i]=false;
}
System_ROOT::~System_ROOT(){
    for(GLuint i = 0; i < Timers.size(); i++)
        delete Timers[i];
}
bool System_ROOT::Create(void){
    srand((unsigned)time(0));
    bool isCreated = Resources.Init_Resource();

    for(GLuint j=0;j<DimOfModels.size();j++)
        if(DimOfModels[j]->SubType==0)
            DimOfSysModel.push_back(DimOfModels[j]);

    for(GLuint j=0;j<DimOfModels.size();j++)
        if(!(DimOfModels[j]->SubType==0))
            DimOfModel.push_back(DimOfModels[j]);

    DimOfModels.clear();

    for(GLuint i=0;i<DimOfModel.size();i++)
        DimOfModel[i]->EventsHandler(ME_CREATE,NULL);

    for(GLuint i=0;i<DimOfSysModel.size();i++)
        DimOfSysModel[i]->EventsHandler(ME_CREATE,NULL);

    return isCreated;
}
bool System_ROOT::Draw(void){
    GLuint *nl;
    nl = new GLuint;
    for(GLuint i=0;i<NumLevelDraw;i++){
        for(GLuint k=0;k<DimOfSysModel.size();k++){
            *nl=i;
            DimOfSysModel[k]->EventsHandler(ME_DRAW,nl);
        }
        for(GLuint j=0;j<DimOfModel.size();j++){
            *nl=i;
            if((DimOfModel[j]->OnlyDraw&&DrawMode)||(!DrawMode))
                DimOfModel[j]->EventsHandler(ME_DRAW,nl);
        }
    }
    delete nl;
    return true;
}
bool System_ROOT::Timer(){
    TimerPlus();
}
bool System_ROOT::MouseUp(int mButton){
       switch(mButton){
    case Qt::LeftButton:
        Mouse.L = S_UP;
        goto MouseClick;
    case Qt::RightButton:
        Mouse.L = S_UP;
        goto MouseClick;
    case Qt::MiddleButton:
        Mouse.L = S_UP;
        goto MouseClick;
    }
MouseClick:
        int TypeEvent =  ME_MOUSECLICK;
        for(GLuint i=0;i<DimOfModel.size();i++){
            if((DimOfModel[i]->NotPaused&&Pause)||(!Pause))
                DimOfModel[i]->EventsHandler(TypeEvent,NULL);
        }
        for(GLuint k=0;k<DimOfSysModel.size();k++){
            DimOfSysModel[k]->EventsHandler(TypeEvent,NULL);
        }
        Mouse.L = Mouse.R = Mouse.M = 0;
        return true;

}
bool System_ROOT::MouseDown(int mButton){
       switch(mButton){
    case Qt::LeftButton:
        Mouse.L = S_DOWN;
        goto MouseClick;
    case Qt::RightButton:
        Mouse.L = S_DOWN;
        goto MouseClick;
    case Qt::MiddleButton:
        Mouse.L = S_DOWN;
        goto MouseClick;
    }
MouseClick:
        int TypeEvent =  ME_MOUSECLICK;
        for(GLuint i=0;i<DimOfModel.size();i++){
            if((DimOfModel[i]->NotPaused&&Pause)||(!Pause))
                DimOfModel[i]->EventsHandler(TypeEvent,NULL);
        }
        for(GLuint k=0;k<DimOfSysModel.size();k++){
            DimOfSysModel[k]->EventsHandler(TypeEvent,NULL);
        }
        Mouse.L = Mouse.R = Mouse.M = 0;
        return true;
}
bool System_ROOT::MouseMove(int x, int y){
    Mouse.x = x;
    Mouse.y = y;
    for(GLuint i=0;i<DimOfModel.size();i++){
        if((DimOfModel[i]->NotPaused&&Pause)||(!Pause))
            DimOfModel[i]->EventsHandler(ME_MOUSEMOVE,NULL);
    }
    for(GLuint k=0;k<DimOfSysModel.size();k++){
        DimOfSysModel[k]->EventsHandler(ME_MOUSEMOVE,NULL);
    }
    return true;
}
bool System_ROOT::KeyDown(int key){
    if((key < 0) || (key > 255))
        return false;
    Keys[key]=true;
    for(GLuint i=0;i<DimOfModel.size();i++){
        if((DimOfModel[i]->NotPaused&&Pause)||(!Pause))
            DimOfModel[i]->EventsHandler(ME_KEYEVENT,NULL);
    }
    for(GLuint k=0;k<DimOfSysModel.size();k++){
        DimOfSysModel[k]->EventsHandler(ME_KEYEVENT,NULL);
    }
    return true;
}
bool System_ROOT::KeyUp(int key){
    if((key < 0) || (key > 255))
        return false;
    Keys[key]=false;
    for(GLuint i=0;i<DimOfModel.size();i++){
        if((DimOfModel[i]->NotPaused&&Pause)||(!Pause))
            DimOfModel[i]->EventsHandler(ME_KEYEVENT,NULL);
    }
    for(GLuint k=0;k<DimOfSysModel.size();k++){
        DimOfSysModel[k]->EventsHandler(ME_KEYEVENT,NULL);
    }
    return true;
}
bool System_ROOT::Destroy(){
       Resources.DisResources();
}
int System_ROOT::AddTimer(GLuint timeSek){
    if(timeSek<=0)
        return -1;
    for(GLuint i=0;i<Timers.size();i++)
        if(timeSek==Timers[i]->MaxTime)
            return -2;
    SysTimer* ntm=new SysTimer;
    ntm->CurTime=0;
    ntm->MaxTime=timeSek;
    Timers.push_back(ntm);
    return Timers.size()-1;
}
void* System_ROOT::PutEventToQueue(int SizeOfData,unsigned int mess,unsigned int _To){
    if(!mess)
        return NULL;
    Message M;

    M.To=_To;
    M.Mess=mess;
    if(SizeOfData){
        M.DataFull=true;
        M.Data=malloc(SizeOfData);
    }
    else{
        M.DataFull=false;
        M.Data=NULL;
    }
    EQ.push_back(M);
    return M.Data;
}
bool System_ROOT::GetKeyStatus(short n){
    if(n >= 0 && n < 256)
        return Keys[n];
    else
        return false;
}
sMouse System_ROOT::GetMouseStatus(void){
    return Mouse;
}

