#ifdef PHYSICS_H
#define PHYSICS_H

#include <math.h>

#include "data.h"

// работает
Error Move(Checker& ch, Real time) {
    ch.speed.x *= ch.rub;
    ch.speed.y *= ch.rub;

    ch.coord.x += ch.speed.x * time;
    ch.coord.y += ch.speed.y * time;

    return OK;
}


Error Clash(Checker& ch, Real _phi) {

    double phi = ch.speed.y > 0 ? _phi : _phi + M_PI;
    double ksi = atan(ch.speed.y / ch.speed.x); // если при делении на 0 получится INFINITY, то всё класно

    // над этим надо подумать
    double dir = ch.speed.x >= 0 ? 2 * phi - ksi : dir = 2 * phi - (pi + ksi);

    ch.speed.x = len * cos(dir);
    ch.speed.y = len * sin(dir);
    return 0;
}

Error Clash(Checker& ch, Wall& w) {

    ch.speed.x *= ch.rub * w.rub;
    ch.speed.y *= ch.rub * w.rub;

    Clash(ch, w.phi);
    return OK;
}

Error Clash(Checker& ch1, Checker& ch2) {
    int _rub = ch1.rub * ch2.rub;
    ch1.speed.x *= _rub;
    ch1.speed.y *= _rub;
    ch2.speed.x *= _rub;
    ch2.speed.y *= _rub;

    Clash(ch1, 0);
    Clash(ch2, 0);
    return OK;
}

#endif // PHYSICS_H
