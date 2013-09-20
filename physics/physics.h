#ifdef CLASH_H
#define CLASH_H

#include <math.h>
#include "data.h"

// двигать
Error Move(Checker& ch, Real time);
// от плоскости под углом
Error Clash(Checker& ch, Real phi);
// от стены
Error Clash(Checker& ch, Wall& w);
// от другой шашки
Error Clash(Checker& ch1, Checker& ch2);

#endif // CLASH_H
