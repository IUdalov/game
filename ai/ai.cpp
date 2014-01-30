
#include "ai.h"
#define PERIOD						1.	/* need 5-20 mlsc */
#define FIRST_FOUR_CHECKERS_ITER	36
#define OTHER_CHECKERS_ITER			1
#define MAX_X						1024
#define MAX_Y						768
#define DEBUG						0

namespace AI
{
vector<AiChecker>	vFriends;
vector<AiChecker>	vEnemys;
INDIan::Rect		fieldRect;
double				maxSpeed = 1.;

/*
 =======================================================================================================================
    Returns distance between phCheckers.
 =======================================================================================================================
 */
double FindDistance(PhChecker chk1, PhChecker chk2)
{
	return sqrt(pow(chk1.coord.x - chk2.coord.x, 2) + pow(chk1.coord.y - chk2.coord.y, 2));
}

/*
 =======================================================================================================================
       Checks for collision. Being called too often seems like not very optimal choice.
 =======================================================================================================================
 */
int CheckForCollision(AiChecker from, AiChecker to, vector<AiChecker> friends, vector<AiChecker> enemys)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	double	k = (to.phChecker.coord.y - from.phChecker.coord.y) / (to.phChecker.coord.x - from.phChecker.coord.x);
	double	b = from.phChecker.coord.y - k * from.phChecker.coord.x;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if((to.phChecker.coord.y < from.phChecker.coord.y))
	{
		for(int j = 0; j < (int) enemys.size(); j++)
		{
			if
			(
				(enemys[j].phChecker.coord.y < from.phChecker.coord.y)	/* if the checker's normal is on the line */
			&&	(
					!((enemys[j].phChecker.coord.x == to.phChecker.coord.x)
					&&	(enemys[j].phChecker.coord.y == to.phChecker.coord.y)
					)
				)	/* it's not the same checker */
			&&	(
					(fabs(k * enemys[j].phChecker.coord.x - enemys[j].phChecker.coord.y + b) / (sqrt(pow(k, 2) + 1))) <
						(max(from.phChecker.radius, to.phChecker.radius) + enemys[j].phChecker.radius)
				)
			) return 1;
		}

		for(int j = 0; j < (int) friends.size(); j++)
		{
			if
			(
				(friends[j].phChecker.coord.y < from.phChecker.coord.y) /* if the checker's normal is on the line */
			&&	(
					!((friends[j].phChecker.coord.x == from.phChecker.coord.x)
					&&	(friends[j].phChecker.coord.y == from.phChecker.coord.y)
					)
				)	/* it's not the same checker */
			&&	((fabs(k * friends[j].phChecker.coord.x - friends[j].phChecker.coord.y + b) / (sqrt(pow(k, 2) + 1))) < (max(from.phChecker.radius, to.phChecker.radius) + friends[j].phChecker.radius))
			) return 1;
		}
	}
	else
	{
		for(int j = 0; j < (int) enemys.size(); j++)
		{
			if
			(
				(enemys[j].phChecker.coord.y >= from.phChecker.coord.y)		/* if the checker's normal is on the line */
			&&	(enemys[j].phChecker.coord.x != to.phChecker.coord.x)
			&&	(enemys[j].phChecker.coord.y != to.phChecker.coord.y)		/* it's not the same checker */
			&&	(
					(fabs(k * enemys[j].phChecker.coord.x - enemys[j].phChecker.coord.y + b) / (sqrt(pow(k, 2) + 1))) <
						(max(from.phChecker.radius, to.phChecker.radius) + enemys[j].phChecker.radius)
				)
			) return 1;
		}

		for(int j = 0; j < (int) friends.size(); j++)
		{
			if
			(
				(friends[j].phChecker.coord.y >= from.phChecker.coord.y)	/* if the checker's normal is on the line */
			&&	(
					!((friends[j].phChecker.coord.x == from.phChecker.coord.x)
					&&	(friends[j].phChecker.coord.y == from.phChecker.coord.y)
					)
				)	/* it's not the same checker */
			&&	((fabs(k * friends[j].phChecker.coord.x - friends[j].phChecker.coord.y + b) / (sqrt(pow(k, 2) + 1))) < (max(from.phChecker.radius, to.phChecker.radius) + friends[j].phChecker.radius))
			) return 1;
		}
	}

	return 0;
}

/*
 =======================================================================================================================
    Checks whether the checker "to" is reachable from the position of "from".
 =======================================================================================================================
 */
int Reachable(AiChecker from, AiChecker to, vector<AiChecker> friends, vector<AiChecker> enemys)
{
	double	k = (to.phChecker.coord.y - from.phChecker.coord.y) / (to.phChecker.coord.x - from.phChecker.coord.x);
    double	b = from.phChecker.coord.y - k * from.phChecker.coord.x;

	if((to.phChecker.coord.y < from.phChecker.coord.y))
	{
		for(int j = 0; j < (int) enemys.size(); j++)
		{
			if
			(
				(enemys[j].phChecker.coord.y < from.phChecker.coord.y)
			&&	(enemys[j].phChecker.coord.y > to.phChecker.coord.y)	/* if the checker's normal is on the line */
			&&	(
					!((enemys[j].phChecker.coord.x == to.phChecker.coord.x)
					&&	(enemys[j].phChecker.coord.y == to.phChecker.coord.y)
					)
				)
			&&	(
					(fabs(k * enemys[j].phChecker.coord.x - enemys[j].phChecker.coord.y + b) / (sqrt(pow(k, 2) + 1))) <
						(max(from.phChecker.radius, to.phChecker.radius) + enemys[j].phChecker.radius)
				)
			) return 0;
		}

		for(int j = 0; j < (int) friends.size(); j++)
		{
			if
			(
				(friends[j].phChecker.coord.y < from.phChecker.coord.y)
			&&	(enemys[j].phChecker.coord.y > to.phChecker.coord.y)	/* if the checker's normal is on the line */
			&&	(
					!((friends[j].phChecker.coord.x == from.phChecker.coord.x)
					&&	(friends[j].phChecker.coord.y == from.phChecker.coord.y)
					)
				)	/* it's not the same checker */
			&&	((fabs(k * friends[j].phChecker.coord.x - friends[j].phChecker.coord.y + b) / (sqrt(pow(k, 2) + 1))) < (max(from.phChecker.radius, to.phChecker.radius) + friends[j].phChecker.radius))
			) return 0;
		}
	}
	else
	{
		for(int j = 0; j < (int) enemys.size(); j++)
		{
			if
			(
				(enemys[j].phChecker.coord.y >= from.phChecker.coord.y)
			&&	(enemys[j].phChecker.coord.y < to.phChecker.coord.y)		/* if the checker's normal is on the line */
			&&	(
					!((enemys[j].phChecker.coord.x == to.phChecker.coord.x)
					&&	(enemys[j].phChecker.coord.y == to.phChecker.coord.y)
					)
				)
			&&	(
					(fabs(k * enemys[j].phChecker.coord.x - enemys[j].phChecker.coord.y + b) / (sqrt(pow(k, 2) + 1))) <
						(max(from.phChecker.radius, to.phChecker.radius) + enemys[j].phChecker.radius)
				)
			) return 0;
		}

		for(int j = 0; j < (int) friends.size(); j++)
		{
			if
			(
				(friends[j].phChecker.coord.y >= from.phChecker.coord.y)	/* if the checker's normal is on the line */
			&&	(enemys[j].phChecker.coord.y < to.phChecker.coord.y)
			&&	(
					!((friends[j].phChecker.coord.x == from.phChecker.coord.x)
					&&	(friends[j].phChecker.coord.y == from.phChecker.coord.y)
					)
				)	/* it's not the same checker */
			&&	((fabs(k * friends[j].phChecker.coord.x - friends[j].phChecker.coord.y + b) / (sqrt(pow(k, 2) + 1))) < (max(from.phChecker.radius, to.phChecker.radius) + friends[j].phChecker.radius))
			) return 0;
		}
	}

	return 1;
}

/*
 =======================================================================================================================
    Finds the position of highest value of matrix.
 =======================================================================================================================
 */
void FindHighestInMatrix(double **matrix, int *iHigh, int *jHigh, int iMax, int jMax)
{
	*iHigh = 0;
	*jHigh = 0;
	for(int i = 0; i < iMax; i++)
		for(int j = 0; j < jMax; j++)
			if(matrix[i][j] > matrix[*iHigh][*jHigh])
			{
				*iHigh = i;
				*jHigh = j;
			}

	return;
}

/*
 =======================================================================================================================
    Simulates :)
    We have an array of movingCheckers, which we move in a cycle, till all of them stop.
 =======================================================================================================================
 */
double Simulate(INDIan::DCoord v, int _i, vector<AiChecker> friends, vector<AiChecker> enemys)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	vector<AiChecker *> movingCheckers;
    bool				isAlreadyMoving;	// potential bug *
	bool				isYour;
	double				profit = 0;
	int					num = 0;
    friends[_i].phChecker.speed.x = v.x;
    friends[_i].phChecker.speed.y = v.y;
    movingCheckers.push_back(&friends[_i]);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	while(movingCheckers.size() > 0)
    {
		for(int k = 0; k < (int) movingCheckers.size(); k++)
        {
#if DEBUG
            FILE	*stream;

			stream = fopen("checkers.txt", "a");
			fprintf
			(
				stream,
				"Checker %d:[%f;%f] has radius %f speed(x)=%f speed(y)=%f \n",
				k,
				movingCheckers[k]->phChecker.coord.x,
				movingCheckers[k]->phChecker.coord.y,
				movingCheckers[k]->phChecker.radius,
				movingCheckers[k]->phChecker.speed.y,
				movingCheckers[k]->phChecker.speed.x
			);
			fclose(stream);
#endif
			if
			(
				(movingCheckers[k]->phChecker.coord.x < 0 - movingCheckers[k]->phChecker.radius)
			||	(movingCheckers[k]->phChecker.coord.y < 0 - movingCheckers[k]->phChecker.radius)
			||	(movingCheckers[k]->phChecker.coord.x > MAX_X + movingCheckers[k]->phChecker.radius)
			||	(movingCheckers[k]->phChecker.coord.y > MAX_Y + movingCheckers[k]->phChecker.radius)
			)
			{
				isYour = 3;

				for(int i = 0; i < (int) friends.size(); i++)
					if(*movingCheckers[k] == friends[i])
					{
						num = i;
						isYour = 1;
                    }
				for(int i = 0; i < (int) enemys.size(); i++)
					if(*movingCheckers[k] == enemys[i])
					{
						num = i;
						isYour = 0;
                    }
				if(isYour)
				{
					profit -= (int) movingCheckers[k]->phChecker.weight;
					friends.erase(friends.begin() + num);
				}
				else
				{
					profit += (int) movingCheckers[k]->phChecker.weight;
					enemys.erase(enemys.begin() + num);
				}

				if(isYour == 3) profit += 100500;
				movingCheckers.erase(movingCheckers.begin() + k);
				k--;
			}
			else
			{
				if((movingCheckers[k]->phChecker.speed.y == 0) && (movingCheckers[k]->phChecker.speed.x == 0))
				{
					movingCheckers.erase(movingCheckers.begin() + k);
					k--;
				}
				else
				{
					Move(movingCheckers[k]->phChecker, PERIOD);
					for(int l = 0; l < (int) enemys.size(); l++)
					{
						if(!(*movingCheckers[k] == enemys[l]))
						{
							if
							(
								FindDistance(movingCheckers[k]->phChecker, enemys[l].phChecker) <
									(movingCheckers[k]->phChecker.radius + enemys[l].phChecker.radius)
							)
							{
								isAlreadyMoving = 0;
								for(int i = 0; i < (int) movingCheckers.size(); i++)
									if(*movingCheckers[i] == enemys[l]) isAlreadyMoving = 1;
								if(isAlreadyMoving == 0)
								{
									Clash(movingCheckers[k]->phChecker, enemys[l].phChecker);
									movingCheckers.push_back(&enemys[l]);
								}
							}
						}
					}

					for(int l = 0; l < (int) friends.size(); l++)
					{
						if(!(*movingCheckers[k] == friends[l]))
						{
							if
							(
								FindDistance(movingCheckers[k]->phChecker, friends[l].phChecker) <
									(movingCheckers[k]->phChecker.radius + friends[l].phChecker.radius)
							)
							{
								isAlreadyMoving = 0;
								for(int i = 0; i < (int) movingCheckers.size(); i++)
									if(*movingCheckers[i] == friends[l]) isAlreadyMoving = 1;
								if(isAlreadyMoving == 0)
								{
									Clash(movingCheckers[k]->phChecker, friends[l].phChecker);
									movingCheckers.push_back(&friends[l]);
								}
							}
						}	/* for */
					}
				}			/* else ( not zero speed) */
			}	/* else ( not outta field) */
        }	/* for */
    }	/* while */

	return profit;
}

/*
 =======================================================================================================================
    Creates copy of current checker's state and analizes all the possibilities.
 =======================================================================================================================
 */
INDIan::DCoord CallSimulate(int *iHigh, int iMax, int jMax)
{

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    *iHigh = 0;
	INDIan::DCoord		curVector = { 1, 0 };
	INDIan::DCoord		c = { 0, 0 };
	INDIan::DCoord		bestVector = curVector;
	int					maxProfit = 0;
	int					curProfit = 0;
	double				angle;
	double				length = maxSpeed;
	int					nIter = 0;
	vector<AiChecker>	copyOfFriends;
    vector<AiChecker>	copyOfEnemys;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

    for(int i = 0; i < (int) vFriends.size(); i++)
        copyOfFriends.push_back(vFriends[i]);

    for(int i = 0; i < (int) vEnemys.size(); i++)
        copyOfEnemys.push_back(vEnemys[i]);

	for(int i = 0; i < iMax; i++)
	{
		for(int j = 0; j < jMax; j++)
		{
			if(i < 4)
				nIter = FIRST_FOUR_CHECKERS_ITER;
			else
				nIter = OTHER_CHECKERS_ITER;
			for(int iteration = 0; iteration < nIter; iteration++)
			{
				curVector = { 1, 0 };
				curVector = INDIan::vect_mult_d(curVector, length);
				if((copyOfEnemys[j].phChecker.coord.x - copyOfFriends[i].phChecker.coord.x) != 0)
				{
					angle = atan2
						(
							copyOfEnemys[j].phChecker.coord.y - copyOfFriends[i].phChecker.coord.y,
							copyOfEnemys[j].phChecker.coord.x - copyOfFriends[i].phChecker.coord.x
						);
				}
				else
					angle = M_PI / 2;
				angle += pow(-1, iteration) * iteration * M_PI / (8 * nIter);	/* now it's linear */
				if(angle < -M_PI) angle = 2 * M_PI + angle;
				if(angle > M_PI) angle = -2 * M_PI + angle;
				curVector = INDIan::TurnPoint(curVector, c, angle);

				curProfit = Simulate(curVector, i, copyOfFriends, copyOfEnemys);

#if DEBUG
				FILE	*stream;
				stream = fopen("curProfits.txt", "a");
				fprintf
				(
					stream,
					"Profit of %i checker for angle %f.5 is %i //Iteration = %i \n",
					i,
					angle * 57.295779513,
					curProfit,
					iteration
				);
				fclose(stream);
#endif
				if(curProfit > maxProfit)
				{
					maxProfit = curProfit;
					bestVector = curVector;
					*iHigh = i;
				}
			}
		}
	}

	copyOfFriends.clear();
	copyOfEnemys.clear();

	return bestVector;
}

/*
 =======================================================================================================================
    Obsolete function, may be used later for pre-preprocessing the alternatives.
    Being called for specific "friend" checker(row), creates the array of values per every "enemy" checker:
        0, if unreachable
        radius^2, if reachable.
 =======================================================================================================================
 */
void CalcProfitInTableRowNew(int row, double *tableRow)
{
	for(int j = 0; j < (int) vEnemys.size(); j++)
	{
		if(Reachable(vFriends[row], vEnemys[j], vFriends, vEnemys))
			tableRow[j] = vFriends[row].phChecker.radius * vEnemys[j].phChecker.radius;
		else
			tableRow[j] = 0;
	}

	return;
}

/*
 =======================================================================================================================
    This function is called from outside whenever it's needed for AI to MakeStep.
 =======================================================================================================================
 */
INDIan::IDn MakeStep()
{

#if DEBUG
    FILE	*stream;
	stream = fopen("curProfits.txt", "w");
	fclose(stream);
	stream = fopen("checkers.txt", "w");
	fclose(stream);
#endif

	int				chosenChecker = 0;
    INDIan::DCoord	v = CallSimulate(&chosenChecker, vFriends.size(), vEnemys.size());//main call

	vFriends[chosenChecker].phChecker.speed.x = v.x;
	vFriends[chosenChecker].phChecker.speed.y = v.y;
	return vFriends[chosenChecker].id;
}

void Disposal()
{
}

void AddFriend(AiChecker checker)
{
	vFriends.push_back(checker);
}

void AddEnemy(AiChecker checker)
{
	vEnemys.push_back(checker);
}

void ClearFriends()
{
	vFriends.clear();
}

void ClearEnemys()
{
	vEnemys.clear();
}

void ClearAll()
{
	ClearEnemys();
	ClearFriends();
}

void SetFieldRect(INDIan::Rect rect)
{
	fieldRect = rect;
}

AiChecker *GetFriend(INDIan::IDn id)
{
    vector<AiChecker>::iterator iter;

	for(iter = vFriends.begin(); iter != vFriends.end(); iter++)
	{
		if(iter->id == id) return &(*iter);
	}

	return NULL;
}


AiChecker *GetEnemy(INDIan::IDn id)
{
    vector<AiChecker>::iterator iter;

	for(iter = vEnemys.begin(); iter != vEnemys.end(); iter++)
	{
		if(iter->id == id) return &(*iter);
	}

	return NULL;
}

void SetMaxSpeed(double max)
{
	maxSpeed = max;
}
}
