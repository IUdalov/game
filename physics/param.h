#ifndef PARAM_H
#define PARAM_H

/*
 * Планируется реализовывать арифметику в целых числах
 *
 * для Spring, Weight, Speed 1000 эквивалентна одной 1 из классической физики
 * те Spring::normal = 1000 означает что удар абсолютно упругий
 */

typedef int T;
typedef int Error;

const double pi = 3.1416;
const Error OK = 0;

const T base = 256;
const T baseRub = 16;
const T baseTime = 16;


namespace Spring {
    const T inert = 0;
    const T soft = base / 2;
    const T normal = base;
    const T power = base * 3 / 2;
    const T superpower = base * 2;
}

namespace Weight {
    const T low = base / 2;
    const T normal = base;
    const T high = 2 * base;
}

namespace Rub {
    const T low = 0;
    const T normal = baseRub;
    const T high = baseRub * 2;
}

namespace State {
    const T vertical = pi / 2;
    const T horizontal = 0;
    const T rotated = pi / 4;
}

#endif // PARAM_H
