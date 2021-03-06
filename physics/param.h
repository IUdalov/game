#ifndef PARAM_H
#define PARAM_H

typedef double Real;
typedef int Error;

const Error OK = 0;

const Real MIN_REAL = 0.0000001;
const Real ANGLE_RUB_COEF = 0.01;
namespace Spring {
    const Real inert = 0; // неупругий удар
    const Real soft = 0.7;
    const Real normal = 1.0; // абсолютно упругий удар
    const Real power = 1.5;
    const Real superpower = 2; // суперупругий
}

namespace Weight {
    const Real low = 1;
    const Real normal = 2.25;
    const Real huge =  4;
}

namespace Rub {
    const Real low = 0.00001; // почти нет трения
    const Real normal = 1.5;  // адекватное трение
    const Real high = 2.5;
}

namespace State {
    const Real vertical = M_PI / 2;
    const Real horizontal = 0;
    const Real rotated = M_PI / 4;
}

namespace Radius {
    const Real small = 10;
    const Real normal = 15;
    const Real big = 20;
}

#endif // PARAM_H
