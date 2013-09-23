#include "physics.h"

inline Real RoundConPi(Real phi) {
    return phi; //- M_PI * trunc(phi / M_PI);
}

// вроде работает, от скуки можно пооптимизировать
Error Move(PhChecker& ch, Real time) {
    Real v = sqrt(ch.speed.x * ch.speed.x + ch.speed.y * ch.speed.y) - ch.rub;
    if (v < MIN_SPEED) {
        ch.speed.x = 0;
        ch.speed.y = 0;
    }

    Real dir = atan(ch.speed.y / ch.speed.x);
    ch.speed.x = v * cos(dir);
    ch.speed.y = v * sin(dir);

    ch.coord.x += ch.speed.x * time;
    ch.coord.y += ch.speed.y * time;
    return OK;
}

Error Clash(PhChecker& ch, Real _phi) {
    //ch.speed.x = - ch.speed.x;
    //ch.speed.y = - ch.speed.y;

    Real v = sqrt(pow(ch.speed.x, 2) + pow(ch.speed.y, 2));
    Real phi = RoundConPi(_phi);

    Real ksi = atan(ch.speed.y / ch.speed.x); // если при делении на 0 получится INFINITY, то всё класно, если арктангенс посчитается вобще зашибись
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

    // угол соуарения
    Real conClash = atan((ch1.coord.y - ch2.coord.y) / (ch1.coord.x - ch2.coord.x)) + M_PI / 2;
    Clash(ch1, conClash);
    Clash(ch2, conClash);

    // скитаем углы для восстановления скорости по ним
    Real phi1 = ch1.speed.x > 0 ? atan(ch1.speed.y / ch1.speed.x) : atan(ch1.speed.y / ch1.speed.x) + M_PI;
    Real phi2 = ch2.speed.x > 0 ? atan(ch2.speed.y / ch2.speed.x) : atan(ch2.speed.y / ch2.speed.x) + M_PI;


    Real v1 = sqrt(pow(ch1.speed.x, 2) + pow(ch1.speed.y, 2));
    Real v2 = sqrt(pow(ch2.speed.x, 2) + pow(ch2.speed.y, 2));
    Real m1 = ch1.weight, m2 = ch2.weight;
    Real a = m1*m2 + m2*m2;
    Real b = - (m1*m2*v1 + m2*m2*v2);
    Real c = -m1*m2*v2*v2 + m2*m2*v2*v2 + 2*m1*v1*m2*v2;

    Real vn2 = (b + sqrt(b * b - a * c)) / a;
    Real vn1 = (m1*v1 + m2*v2 - m2*vn2) / m1;

    // формирование результируещего вектора скорости
    ch1.speed.x = vn1 * cos(phi1);
    ch1.speed.y = vn1 * sin(phi1);
    ch2.speed.x = vn2 * cos(phi2);
    ch2.speed.y = vn2 * sin(phi2);

    return OK;
}
