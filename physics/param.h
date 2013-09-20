#ifdef PARAM_H
#define PARAM_H

/* N/A
 * Планируется реализовывать арифметику в целых числах
 *
 * для Spring, Weight, Speed 1000 эквивалентна одной 1 из классической физики
 * те Spring::normal = 1000 означает что удар абсолютно упругий
 */

typedef double Real;
typedef int Error;

const double pi = 3.1416;
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
    const Real low;
    const Real normal = baseRub;
    const Real high = baseRub * 2;
}

namespace State {
    const Real vertical = pi / 2;
    const Real horizontal = 0;
    const Real rotated = pi / 4;
}

#endif // PARAM_H
