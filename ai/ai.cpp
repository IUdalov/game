#include "ai.h"

namespace AI{
    vector<AiChecker> vFriends;
    vector<AiChecker> vEnemys;
    INDIan::Rect fieldRect;
    double maxSpeed = 1.;



    double FindDistance(PhChecker chk1, PhChecker chk2){
        return sqrt(pow(chk1.coord.x-chk2.coord.x,2)+pow(chk1.coord.y-chk2.coord.y,2));
    }

    int CheckForCollision(AiChecker from, AiChecker to, vector<AiChecker> Friends, vector<AiChecker> Enemys){

       double k=(to.phChecker.coord.y-from.phChecker.coord.y)/(to.phChecker.coord.x-from.phChecker.coord.x);
       double b=from.phChecker.coord.y-k*from.phChecker.coord.x;

       if((to.phChecker.coord.y<from.phChecker.coord.y)){
           for(int j=0;j<Enemys.size();j++)
               if((Enemys[j].phChecker.coord.y<from.phChecker.coord.y)//if the checker's normal is on the line
                       &&(Enemys[j].phChecker.coord.x!=to.phChecker.coord.x)&&(Friends[j].phChecker.coord.y!=from.phChecker.coord.y)//it's not the same checker
                       &&(( fabs(k*Enemys[j].phChecker.coord.x-Enemys[j].phChecker.coord.y+b)/(sqrt(pow(k,2)+1)))<(max(from.phChecker.radius,to.phChecker.radius)+Enemys[j].phChecker.radius)))
                       return 1;
           for(int j=0;j<Friends.size();j++)
               if((Friends[j].phChecker.coord.y<from.phChecker.coord.y)//if the checker's normal is on the line
                       &&(Friends[j].phChecker.coord.x!=from.phChecker.coord.x)&&(Friends[j].phChecker.coord.y!=from.phChecker.coord.y)//it's not the same checker
                       &&(( fabs(k*Friends[j].phChecker.coord.x-Friends[j].phChecker.coord.y+b)/(sqrt(pow(k,2)+1)))<(max(from.phChecker.radius,to.phChecker.radius)+Friends[j].phChecker.radius)))
                       return 1;
            }
       else
       {
                  for(int j=0;j<Enemys.size();j++)
                      if((Enemys[j].phChecker.coord.y>=from.phChecker.coord.y)//if the checker's normal is on the line
                              &&(Enemys[j].phChecker.coord.x!=to.phChecker.coord.x)&&(Friends[j].phChecker.coord.y!=from.phChecker.coord.y)//it's not the same checker
                              &&(( fabs(k*Enemys[j].phChecker.coord.x-Enemys[j].phChecker.coord.y+b)/(sqrt(pow(k,2)+1)))<(max(from.phChecker.radius,to.phChecker.radius)+Enemys[j].phChecker.radius)))
                              return 1;
                  for(int j=0;j<Friends.size();j++)
                      if((Friends[j].phChecker.coord.y>=from.phChecker.coord.y)//if the checker's normal is on the line
                              &&(Friends[j].phChecker.coord.x!=from.phChecker.coord.x)&&(Friends[j].phChecker.coord.y!=from.phChecker.coord.y)//it's not the same checker
                              &&(( fabs(k*Friends[j].phChecker.coord.x-Friends[j].phChecker.coord.y+b)/(sqrt(pow(k,2)+1)))<(max(from.phChecker.radius,to.phChecker.radius)+Friends[j].phChecker.radius)))
                              return 1;
        }


        return 0;
    }


    void FindHighestInMatrix(double** Matrix,int* iHigh, int* jHigh ,int iMax, int jMax)
    {
        *iHigh=0;
        *jHigh=0;
        for(int i=0;i<iMax;i++)
            for(int j=0;j<jMax;j++)
                if (Matrix[i][j]>Matrix[*iHigh][*jHigh]){
                    *iHigh=i;
                    *jHigh=j;

            }
        return;
    }

    void CalcProfitInTableRow(int row,double* TableRow)
    {
        for(int j=0;j<vEnemys.size();j++)
            TableRow[j]=pow(vFriends[row].phChecker.radius,2)*pow(vEnemys[j].phChecker.radius,2)/FindDistance(vFriends[row].phChecker,vEnemys[j].phChecker)*(1.01-CheckForCollision(vFriends[row],vEnemys[j],vFriends,vEnemys));
        return;
    }

    INDIan::IDn MakeStep(){
        double ** ProfitTable= new double*[vFriends.size()];
        for(int i=0;i<vFriends.size();i++)
            ProfitTable[i]=new double[vEnemys.size()];
        for(int i=0;i<vFriends.size();i++)
            CalcProfitInTableRow(i,ProfitTable[i]);
        int num,chosen_enemy;
        FindHighestInMatrix(ProfitTable,&num,&chosen_enemy,vFriends.size(),vEnemys.size());
        //int num = CalcPlaceProfit(); // позднее буду перебирать несколько шашек а не только ту, что вернул CalcPlaceProfit;
        INDIan::DCoord v = {1, 0};
        INDIan::DCoord c = {0, 0};
        double length = (int)maxSpeed;
       // int chosen_enemy=CalcEnemyProfit(num);
        v = INDIan::vect_mult_d(v, length);
        double angle;
        if((vEnemys[chosen_enemy].phChecker.coord.x-vFriends[num].phChecker.coord.x)!=0)
            angle=atan2(vEnemys[chosen_enemy].phChecker.coord.y-vFriends[num].phChecker.coord.y,vEnemys[chosen_enemy].phChecker.coord.x-vFriends[num].phChecker.coord.x);
        else
            angle=M_PI/2;
        v = INDIan::TurnPoint(v, c, angle); // поворачиваем v вокруг c на угол angle
        vFriends[num].phChecker.speed.x = v.x;
        vFriends[num].phChecker.speed.y = v.y;
        for(int i=0;i<vFriends.size();i++)
            delete[] ProfitTable[i];
        delete[] ProfitTable;
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
