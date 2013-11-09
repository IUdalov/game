#include "ai.h"


namespace AI{
    vector<AiChecker> vFriends;
    vector<AiChecker> vEnemys;
    INDIan::Rect fieldRect;
    double maxSpeed = 1.;

    INDIan::IDn MakeStep(){
        int num = qrand() % int(vFriends.size()); // берем рандомную шашку
        INDIan::DCoord v = {0, 1}; // вектор скорости, пока просто нулевой длины
        INDIan::DCoord c = {0, 0}; // это центр относительно которого будем крутить вектор
        double length = double(qrand() % (int)maxSpeed); // длинна вектора
        v = INDIan::vect_mult_d(v, length); // домножаем единичный вектор на длинну
        double angle = (double(qrand() % 360)) / M_PI;
        v = INDIan::TurnPoint(v, c, angle); // поворачиваем v вокруг c на угол angle
        vFriends[num].phChecker.speed.x = v.x;
        vFriends[num].phChecker.speed.y = v.y;
        return vFriends[num].id;
    }
    void Disposal(){
    }
    void AddFriend(AiChecker checker){
        vFriends.push_back(checker);
    }
    void AddEnemy(AiChecker checker){
        vEnemys.push_back(checker);
    }
    void ClearFriends(){
        vFriends.clear();
    }
    void ClearEnemys(){
        vEnemys.clear();
    }
    void ClearAll(){
        ClearEnemys();
        ClearFriends();
    }
    void SetFieldRect(INDIan::Rect rect){
        fieldRect = rect;
    }
    AiChecker* GetFriend(INDIan::IDn id){
        vector<AiChecker>::iterator iter;
        for(iter = vFriends.begin(); iter != vFriends.end(); iter++){
            if(iter->id == id)
                return &(*iter);
        }
        return NULL;
    }
    AiChecker* GetEnemy(INDIan::IDn id){
        vector<AiChecker>::iterator iter;
        for(iter = vEnemys.begin(); iter != vEnemys.end(); iter++){
            if(iter->id == id)
                return &(*iter);
        }
        return NULL;
    }
    void SetMaxSpeed(double max){
        maxSpeed = max;
    }
}
