#include "physics.h"
/*
// работает
Error Move(Checker& ch, Real time) {
    ch.speed.x /= ch.rub;
    ch.speed.y /= ch.rub;

    ch.coord.x += ch.speed.x * time;
    ch.coord.y += ch.speed.y * time;

    return OK;
}

Error Clash(Checker& ch, Real _phi) {

    Real phi = _phi > 0 ? : phi + _phi;
    phi = phi - pi * trunk(phi / pi);
    Real len = sqrt(pow(ch.speed.x, 2) + pow(ch.speed.y, 2));
    Real dir = 0;
    Real ksi = ch.speed.x == 0 ? atan(ch.speed.y / ch.speed.x) : INFINITY;

    // над этим надо подумать
    dir = ch.speed.x >= 0 ? 2 * phi - ksi : dir = 2 * phi - (pi + ksi);

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

// no
Error Clash(Checker& ch1, Checker& ch2) {

    return OK;
}
*/
