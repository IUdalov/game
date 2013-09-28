#include "physics.h"

inline Real RoundConPi(Real phi) {
    return phi; //- M_PI * trunc(phi / M_PI);
}

// вроде работает, от скуки можно пооптимизировать
Error Move(PhChecker& ch, Real time) {
    Real v = sqrt( pow( ch.speed.x, 2.) + pow( ch.speed.y, 2.) );
    if (v <= ch.rub) {
        ch.speed.x = 0.;
        ch.speed.y = 0.;
        return OK;
    }

    v -= ch.rub;

    Real dir = ch.speed.x > 0 ? atan(ch.speed.y / ch.speed.x) : atan(ch.speed.y / ch.speed.x) + M_PI;

    ch.speed.x = v * cos(dir);
    ch.speed.y = v * sin(dir);

    ch.coord.x += ch.speed.x * time;
    ch.coord.y += ch.speed.y * time;
    return OK;
}


Error Clash(PhChecker& ch, Real _phi) {

    Real v = sqrt(pow(ch.speed.x, 2) + pow(ch.speed.y, 2));
    Real phi = RoundConPi(_phi);

    Real ksi;
    if (fabs(ch.speed.x) > MIN_SPEED) {
        ksi = atan(ch.speed.y / ch.speed.x);
    } else {
        ksi = 112358;
    }
    // над этим можно подумать
    Real dir = (ch.speed.x > 0) ? (2 * phi - ksi) : (2 * phi - (ksi + M_PI));

    ch.speed.x = v * cos(dir);
    ch.speed.y = v * sin(dir);

    return 0;
}

Error Clash(PhChecker& ch, PhWall& w) {

    ch.speed.x *= ch.spring * w.spring;
    ch.speed.y *= ch.spring * w.spring;

    Clash(ch, w.phi);

    return OK;
}

Error Clash(PhChecker& ch1, PhChecker& ch2) {
    // корректировка скорости в зависимости от упругости
    Real _s = ch1.spring * ch2.spring;

    ch1.speed.x *= _s;
    ch1.speed.y *= _s;
    ch2.speed.x *= _s;
    ch2.speed.y *= _s;

    Real m1 = ch1.weight, m2 = ch2.weight;
    Real v1x = ch1.speed.x, v1y = ch1.speed.y;
    Real v2x = ch2.speed.x, v2y = ch2.speed.y;

    ch1.speed.x = ((m1 - m2) * v1x + 2 * m2 * v2x) / (m1 + m2);
    ch1.speed.y = ((m1 - m2) * v1y + 2 * m2 * v2y) / (m1 + m2);

    ch2.speed.x = (2 * m1 * v1x + (m2 - m1) * v2x) / (m1 + m2);
    ch2.speed.y = (2 * m1 * v1y + (m2 - m1) * v2y) / (m1 + m2);
    return OK;
}
