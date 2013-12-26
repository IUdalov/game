#include "ai.h"
#define PERIOD 1. //need 5-20 mlsc
#define MAX_X 1024
#define MAX_Y 768
namespace AI{
    vector<AiChecker> vFriends;
    vector<AiChecker> vEnemys;
    INDIan::Rect fieldRect;
    double maxSpeed = 1.;



    double FindDistance(PhChecker chk1, PhChecker chk2){
        return sqrt(pow(chk1.coord.x-chk2.coord.x,2)+pow(chk1.coord.y-chk2.coord.y,2));
    }

    int CheckForCollision(AiChecker from, AiChecker to, vector<AiChecker> friends, vector<AiChecker> enemys){

       double k=(to.phChecker.coord.y-from.phChecker.coord.y)/(to.phChecker.coord.x-from.phChecker.coord.x);
       double b=from.phChecker.coord.y-k*from.phChecker.coord.x;

       if((to.phChecker.coord.y<from.phChecker.coord.y)){
           for(int j=0;j<(int)enemys.size();j++)
               if((enemys[j].phChecker.coord.y<from.phChecker.coord.y)//if the checker's normal is on the line
                       &&(!((enemys[j].phChecker.coord.x==to.phChecker.coord.x)&&(enemys[j].phChecker.coord.y==to.phChecker.coord.y)))//it's not the same checker
                       &&(( fabs(k*enemys[j].phChecker.coord.x-enemys[j].phChecker.coord.y+b)/(sqrt(pow(k,2)+1)))<(max(from.phChecker.radius,to.phChecker.radius)+enemys[j].phChecker.radius)))
                       return 1;
           for(int j=0;j<(int)friends.size();j++)
               if((friends[j].phChecker.coord.y<from.phChecker.coord.y)//if the checker's normal is on the line
                       &&(!((friends[j].phChecker.coord.x==from.phChecker.coord.x)&&(friends[j].phChecker.coord.y==from.phChecker.coord.y)))//it's not the same checker
                       &&(( fabs(k*friends[j].phChecker.coord.x-friends[j].phChecker.coord.y+b)/(sqrt(pow(k,2)+1)))<(max(from.phChecker.radius,to.phChecker.radius)+friends[j].phChecker.radius)))
                       return 1;
            }
       else
       {
                  for(int j=0;j<(int)enemys.size();j++)
                      if((enemys[j].phChecker.coord.y>=from.phChecker.coord.y)//if the checker's normal is on the line
                              &&(enemys[j].phChecker.coord.x!=to.phChecker.coord.x)&&(enemys[j].phChecker.coord.y!=to.phChecker.coord.y)//it's not the same checker
                              &&(( fabs(k*enemys[j].phChecker.coord.x-enemys[j].phChecker.coord.y+b)/(sqrt(pow(k,2)+1)))<(max(from.phChecker.radius,to.phChecker.radius)+enemys[j].phChecker.radius)))
                              return 1;
                  for(int j=0;j<(int)friends.size();j++)
                      if((friends[j].phChecker.coord.y>=from.phChecker.coord.y)//if the checker's normal is on the line
                              &&(!((friends[j].phChecker.coord.x==from.phChecker.coord.x)&&(friends[j].phChecker.coord.y==from.phChecker.coord.y)))//it's not the same checker
                              &&(( fabs(k*friends[j].phChecker.coord.x-friends[j].phChecker.coord.y+b)/(sqrt(pow(k,2)+1)))<(max(from.phChecker.radius,to.phChecker.radius)+friends[j].phChecker.radius)))
                              return 1;
        }


        return 0;
    }

    int Reachable(AiChecker from, AiChecker to, vector<AiChecker> friends, vector<AiChecker> enemys){

       double k=(to.phChecker.coord.y-from.phChecker.coord.y)/(to.phChecker.coord.x-from.phChecker.coord.x);
       double b=from.phChecker.coord.y-k*from.phChecker.coord.x;

       if((to.phChecker.coord.y<from.phChecker.coord.y)){
           for(int j=0;j<(int)enemys.size();j++)
               if((enemys[j].phChecker.coord.y<from.phChecker.coord.y)
                       &&(enemys[j].phChecker.coord.y>to.phChecker.coord.y)//if the checker's normal is on the line
                       &&(!((enemys[j].phChecker.coord.x==to.phChecker.coord.x)&&(enemys[j].phChecker.coord.y==to.phChecker.coord.y)))
                       &&(( fabs(k*enemys[j].phChecker.coord.x-enemys[j].phChecker.coord.y+b)/(sqrt(pow(k,2)+1)))<(max(from.phChecker.radius,to.phChecker.radius)+enemys[j].phChecker.radius)))
                       return 0;
           for(int j=0;j<(int)friends.size();j++)
               if((friends[j].phChecker.coord.y<from.phChecker.coord.y)
                       &&(enemys[j].phChecker.coord.y>to.phChecker.coord.y)//if the checker's normal is on the line
                       &&(!((friends[j].phChecker.coord.x==from.phChecker.coord.x)&&(friends[j].phChecker.coord.y==from.phChecker.coord.y)))//it's not the same checker
                      &&(( fabs(k*friends[j].phChecker.coord.x-friends[j].phChecker.coord.y+b)/(sqrt(pow(k,2)+1)))<(max(from.phChecker.radius,to.phChecker.radius)+friends[j].phChecker.radius)))
                       return 0;
            }
       else
       {
                  for(int j=0;j<(int)enemys.size();j++)
                      if((enemys[j].phChecker.coord.y>=from.phChecker.coord.y)
                              &&(enemys[j].phChecker.coord.y<to.phChecker.coord.y)//if the checker's normal is on the line
                              &&(!((enemys[j].phChecker.coord.x==to.phChecker.coord.x)&&(enemys[j].phChecker.coord.y==to.phChecker.coord.y)))
                              &&(( fabs(k*enemys[j].phChecker.coord.x-enemys[j].phChecker.coord.y+b)/(sqrt(pow(k,2)+1)))<(max(from.phChecker.radius,to.phChecker.radius)+enemys[j].phChecker.radius)))
                              return 0;
                  for(int j=0;j<(int)friends.size();j++)
                      if((friends[j].phChecker.coord.y>=from.phChecker.coord.y)//if the checker's normal is on the line
                              &&(enemys[j].phChecker.coord.y<to.phChecker.coord.y)
                              &&(!((friends[j].phChecker.coord.x==from.phChecker.coord.x)&&(friends[j].phChecker.coord.y==from.phChecker.coord.y)))//it's not the same checker
                               &&(( fabs(k*friends[j].phChecker.coord.x-friends[j].phChecker.coord.y+b)/(sqrt(pow(k,2)+1)))<(max(from.phChecker.radius,to.phChecker.radius)+friends[j].phChecker.radius)))
                              return 0;
        }


        return 1;
    }

    void FindHighestInMatrix(double** matrix,int* iHigh, int* jHigh ,int iMax, int jMax)
    {
        *iHigh=0;
        *jHigh=0;
        for(int i=0;i<iMax;i++)
            for(int j=0;j<jMax;j++)
                if (matrix[i][j]>matrix[*iHigh][*jHigh]){
                    *iHigh=i;
                    *jHigh=j;

            }
        return;
    }

    double Simulate(int _i,int _j,vector<PhChecker> friends, vector<PhChecker> enemys){
        vector<PhChecker*> movingCheckers;
        vector<bool> isYours;
        bool isAlreadyMoving;
        double profit=0;
        INDIan::DCoord v = {1, 0};
        INDIan::DCoord c = {0, 0};
        double length = (int)maxSpeed;
        v = INDIan::vect_mult_d(v, length);
        double angle;
        if((enemys[_j].coord.x-friends[_i].coord.x)!=0)
            angle=atan2(enemys[_j].coord.y-friends[_i].coord.y,enemys[_j].coord.x-friends[_i].coord.x);
        else
            angle=M_PI/2;
        v = INDIan::TurnPoint(v, c, angle);
        friends[_i].speed.x = v.x;
        friends[_i].speed.y = v.y;
        //
        movingCheckers.push_back(&friends[_i]);
        isYours.push_back(true);
        while(movingCheckers.size()>0){
            int nMoving=(int)movingCheckers.size();
            for(int k=0;k<nMoving;k++){
                //FILE *stream;
                //stream = fopen("checkers.txt", "a");
                //fprintf (stream, "Checker %d:[%f;%f] has radius %f speed(x)=%f speed(y)=%f \n", k,movingCheckers[k]->coord.x,movingCheckers[k]->coord.y, movingCheckers[k]->radius,movingCheckers[k]->speed.y,movingCheckers[k]->speed.x);
                //fclose(stream);
                if((movingCheckers[k]->coord.x<0)||(movingCheckers[k]->coord.y<0)||(movingCheckers[k]->coord.x>MAX_X)||(movingCheckers[k]->coord.y>MAX_Y)){
                    if(isYours[k]==true)//LOLWUT?
                        profit-=movingCheckers[k]->radius;
                    else
                        profit+=movingCheckers[k]->radius;

                    //stream = fopen("movingcheckers.txt", "a");
                    //fprintf (stream, "Checker %d:[%f;%f] has radius %f speed(x)=%f speed(y)=%f \n", k,movingCheckers[k]->coord.x,movingCheckers[k]->coord.y, movingCheckers[k]->radius,movingCheckers[k]->speed.y,movingCheckers[k]->speed.x);
                    //fclose(stream);
                    movingCheckers.erase(movingCheckers.begin()+k);
                    nMoving--;
                    isYours.erase(isYours.begin()+k);

                    k--;
                }
                else
                    if((movingCheckers[k]->speed.y==0)&&(movingCheckers[k]->speed.x==0)){
                    movingCheckers.erase(movingCheckers.begin()+k);
                    isYours.erase(isYours.begin()+k);
                    k--;
                    nMoving--;
                }
                else{
                    Move(*movingCheckers[k], PERIOD);//WTF CHANGE ME

                    for(int l=0;l<(int)enemys.size();l++)
                          if(movingCheckers[k]!=&enemys[l]){
                        //  if(!((enemys[l].coord.x==movingCheckers[k]->coord.x)&&(enemys[l].coord.y==movingCheckers[k]->coord.y))){
                            if(FindDistance(*movingCheckers[k],enemys[l])<(movingCheckers[k]->radius+enemys[l].radius)){
                                    isAlreadyMoving=0;
                                    for(int i=0;i<(int)movingCheckers.size();i++)
                                        if(movingCheckers[i]==&enemys[l])
                                            isAlreadyMoving=1;
                                    if(isAlreadyMoving==0){
                                        Clash(*movingCheckers[k],enemys[l]);
                                        movingCheckers.push_back(&(enemys[l]));
                                        isYours.push_back(false);
                                    }
                            }
                    }

                    for(int l=0;l<(int)friends.size();l++)
                        if(!((friends[l].coord.x==movingCheckers[k]->coord.x)&&(friends[l].coord.y==movingCheckers[k]->coord.y))){
                            if(FindDistance(*movingCheckers[k],friends[l])<(movingCheckers[k]->radius+friends[l].radius)){
                                isAlreadyMoving=0;
                                for(int i=0;i<(int)movingCheckers.size();i++)
                                    if(movingCheckers[i]==&friends[l])
                                        isAlreadyMoving=1;
                                if(isAlreadyMoving==0){
                                    Clash(*movingCheckers[k],friends[l]);
                                    movingCheckers.push_back(&(friends[l]));
                                    isYours.push_back(true);
                                }
                            }
                    }

                    //if
                }//else
            }//for
        }//while
        return profit;
    }

    void CallSimulate(double** Matrix,int* iHigh, int* jHigh ,int iMax, int jMax){
        *iHigh=0;
        *jHigh=0;
        vector<PhChecker> copyOfFriends;
        for(int i=0;i<(int)vFriends.size();i++)
            copyOfFriends.push_back(vFriends[i].phChecker);

        vector<PhChecker> copyOfEnemys;
        for(int i=0;i<(int)vEnemys.size();i++)
            copyOfEnemys.push_back(vEnemys[i].phChecker);

        for(int i=0;i<iMax;i++)
            for(int j=0;j<jMax;j++){
               // if (Matrix[i][j]>0){
                    Matrix[i][j]=Simulate(i,j,copyOfFriends,copyOfEnemys);
              //  }
            }

      /*
       FILE *stream;
       stream = fopen("matrix.txt", "w");
       for(int i=0;i<iMax;i++){
           for(int j=0;j<jMax;j++)
               fprintf (stream, "%f ", Matrix[i][j]);
           fprintf(stream, "\n ");
       }
       fclose(stream);
        */
        copyOfFriends.clear();
        copyOfEnemys.clear();
        for(int i=0;i<iMax;i++)
            for(int j=0;j<jMax;j++)
                if (Matrix[i][j]>Matrix[*iHigh][*jHigh]){
                    *iHigh=i;
                    *jHigh=j;

            }

    }

    void CalcProfitInTableRow(int row,double* tableRow)
    {
        for(int j=0;j<(int)vEnemys.size();j++)
            tableRow[j]=pow(vFriends[row].phChecker.radius,2)*pow(vEnemys[j].phChecker.radius,2)/FindDistance(vFriends[row].phChecker,vEnemys[j].phChecker)*(1.01-CheckForCollision(vFriends[row],vEnemys[j],vFriends,vEnemys));
        return;
    }

    void CalcProfitInTableRowNew(int row,double* tableRow)
    {
        for(int j=0;j<(int)vEnemys.size();j++){
            if(Reachable(vFriends[row],vEnemys[j],vFriends,vEnemys))
                 tableRow[j]=vFriends[row].phChecker.radius*vEnemys[j].phChecker.radius;
            else
                tableRow[j]=0;
        }
        return;
    }

    INDIan::IDn MakeStep(){
        int num=0,chosen_enemy=0;
        double ** profitTable= new double*[vFriends.size()];
        for(int i=0;i<(int)vFriends.size();i++)
            profitTable[i]=new double[vEnemys.size()];
        for(int i=0;i<(int)vFriends.size();i++)
            CalcProfitInTableRowNew(i,profitTable[i]);
        CallSimulate(profitTable,&num,&chosen_enemy,vFriends.size(),vEnemys.size());
        INDIan::DCoord v = {1, 0};
        INDIan::DCoord c = {0, 0};
        double length = (int)maxSpeed;
        v = INDIan::vect_mult_d(v, length);
        double angle;
        if((vEnemys[chosen_enemy].phChecker.coord.x-vFriends[num].phChecker.coord.x)!=0)
            angle=atan2(vEnemys[chosen_enemy].phChecker.coord.y-vFriends[num].phChecker.coord.y,vEnemys[chosen_enemy].phChecker.coord.x-vFriends[num].phChecker.coord.x);
        else
            angle=M_PI/2;
        v = INDIan::TurnPoint(v, c, angle);
        vFriends[num].phChecker.speed.x = v.x;
        vFriends[num].phChecker.speed.y = v.y;
        for(int i=0;i<(int)vFriends.size();i++)
            delete[] profitTable[i];
        delete[] profitTable;
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
