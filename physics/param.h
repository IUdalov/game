#ifndef PARAM_H
#define PARAM_H

typedef double Real;
typedef int Error;

const Error OK = 0;

const Real MIN_SPEED = 0.0000001;

namespace Spring {
    const Real inert = 0;
    const Real soft = 0.7;
    const Real normal = 1.0; //++купер - правильно сделал
    const Real power = 1.5;
    const Real superpower = 2;
}

namespace Weight {
    const Real low = 10;
    const Real normal = 25;
    const Real huge =  50;
}

namespace Rub {
    const Real low = 1.000001;
    const Real normal = 1.5;//++тож купер
    const Real high = 2.5;
}

namespace State {
    const Real vertical = M_PI / 2;
    const Real horizontal = 0;
    const Real rotated = M_PI / 4;
}

#endif // PARAM_H
