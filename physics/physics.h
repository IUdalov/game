#ifndef PHYSICS_H
#define PHYSICS_H

#include <math.h>

#include "data.h"

//
Real RoundConPi(Real phi);

// передвинуть за время
Error Move(PhChecker& ch, Real time);

// столкнуть со стеной
Error Clash(PhChecker& ch, PhWall& w);

// столкнуть две шашки
Error Clash(PhChecker& ch1, PhChecker& ch2);


#endif // PHYSICS_H
