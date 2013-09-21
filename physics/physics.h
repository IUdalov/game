#ifndef PHYSICS_H
#define PHYSICS_H

#include <math.h>

#include "data.h"

//
inline Real RoundConPi(Real phi);

// передвинуть за время
Error Move(Checker& ch, Real time);

// столкнуть упруго с плоскостью под углом фи
Error Clash(Checker& ch, Real _phi);

// столкнуть со стеной
Error Clash(Checker& ch, Wall& w);

// столкнуть две шашки
Error Clash(Checker& ch1, Checker& ch2);


#endif // PHYSICS_H
