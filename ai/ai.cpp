#include "ai.h"
#include <fstream>

namespace AI{
    vector<AiChecker> vFriends;
    vector<AiChecker> vEnemys;
    INDIan::Rect fieldRect;
    double maxSpeed = 1.;



    double FindDistance(PhChecker chk1, PhChecker chk2){
        return sqrt(pow(chk1.coord.x-chk2.coord.x,2)+pow(chk1.coord.y-chk2.coord.y,2));
    }
    int CalcPlaceProfit(){
        int highest_profit=0;
        for(int i=0;i< vFriends.size();i++)
        {
            vFriends[i].profit=0;
            for(int j=0;j<vEnemys.size();j++)
                vFriends[i].profit+=FindDistance(vFriends[i].phChecker,vEnemys[j].phChecker);
            if(vFriends[i].profit!=0)
                vFriends[i].profit=vFriends[i].phChecker.radius/vFriends[i].profit;
            if(vFriends[i].profit>vFriends[highest_profit].profit)
                highest_profit=i;
        }
        return highest_profit;
    }
    int CalcEnemyProfit(int _num){
        int chosen_enemy=0;
            for(int j=0;j<vEnemys.size();j++){
                vEnemys[j].profit=vEnemys[j].phChecker.radius/FindDistance(vFriends[_num].phChecker,vEnemys[j].phChecker);
                if(vEnemys[j].profit>vEnemys[chosen_enemy].profit)
                    chosen_enemy=j;
            }
        return chosen_enemy;
    }

    INDIan::IDn MakeStep(){

        int num = CalcPlaceProfit(); // позднее буду перебирать несколько шашек а не только ту, что вернул CalcPlaceProfit;
        INDIan::DCoord v = {1, 0};
        INDIan::DCoord c = {0, 0};
        double length = (int)maxSpeed;
        int chosen_enemy=CalcEnemyProfit(num);
        v = INDIan::vect_mult_d(v, length);
        double angle;
        if((vEnemys[chosen_enemy].phChecker.coord.x-vFriends[num].phChecker.coord.x)!=0)
            angle=atan2(vEnemys[chosen_enemy].phChecker.coord.y-vFriends[num].phChecker.coord.y,vEnemys[chosen_enemy].phChecker.coord.x-vFriends[num].phChecker.coord.x);
        else
            angle=M_PI/2;
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
