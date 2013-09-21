#ifndef PARAM_H
#define PARAM_H

typedef double Real;
typedef int Error;

const Error OK = 0;

const Real base = 256;
const Real baseRub = 16;
const Real baseTime = 16;


namespace Spring {
    const Real inert = 0;
    const Real soft = base / 2;
    const Real normal = base;
    const Real power = base * 3 / 2;
    const Real superpower = base * 2;
}

namespace Weight {
    const Real low = base / 2;
    const Real normal = 23;
    const Real huge =  3;
}

namespace Rub {
    const Real low = 10;
    const Real normal = baseRub;
    const Real high = baseRub * 2;
}

namespace State {
    const Real vertical = M_PI / 2;
    const Real horizontal = 0;
    const Real rotated = M_PI / 4;
}

#endif // PARAM_H
