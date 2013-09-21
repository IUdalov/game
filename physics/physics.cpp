#include "physics.h"

inline Real RoundConPi(Real phi) {
    return phi - M_PI * trunc(phi / M_PI);
}

// работает
Error Move(Checker& ch, Real time) {
    ch.speed.x *= ch.rub;
    ch.speed.y *= ch.rub;

    ch.coord.x += ch.speed.x * time;
    ch.coord.y += ch.speed.y * time;

    return OK;
}

Error Clash(Checker& ch, Real _phi) {
    double v = sqrt(pow(ch.speed.x, 2) + pow(ch.speed.y, 2));
    double phi = RoundConPi(_phi);
    double ksi = atan(ch.speed.y / ch.speed.x); // если при делении на 0 получится INFINITY, то всё класно, если арктангенс посчитается вобще зашибись

    // над этим надо подумать
    double dir = (ch.speed.x > 0) ? (2 * phi - ksi) : (2 * phi - (ksi - M_PI));

    ch.speed.x = v * cos(dir);
    ch.speed.y = v * sin(dir);
    return 0;
}

Error Clash(Checker& ch, Wall& w) {

    ch.speed.x *= ch.spring * w.spring;
    ch.speed.y *= ch.spring * w.spring;

    Clash(ch, w.phi);

    return OK;
}

Error Clash(Checker& ch1, Checker& ch2) {
    // корректировка скорости в зависимости от упругости
    int _s = ch1.spring * ch2.spring;
    ch1.speed.x *= _s;
    ch1.speed.y *= _s;
    ch2.speed.x *= _s;
    ch2.speed.y *= _s;

    // угол соуарения
    Real conClash = atan((ch1.coord.y - ch2.coord.y) / (ch1.coord.x - ch2.coord.x)) + M_PI / 2;
    Clash(ch1, conClash);
    Clash(ch2, conClash);

    // скитаем углы для восстановления скорости по ним
    double phi1 = ch1.speed.x > 0 ? atan(ch1.speed.y / ch1.speed.x) : atan(ch1.speed.y / ch1.speed.x) + M_PI;
    double phi2 = ch2.speed.x > 0 ? atan(ch2.speed.y / ch2.speed.x) : atan(ch2.speed.y / ch2.speed.x) + M_PI;


    Real v1 = sqrt(pow(ch1.speed.x, 2) + pow(ch1.speed.y, 2));
    Real v2 = sqrt(pow(ch2.speed.x, 2) + pow(ch2.speed.y, 2));
    Real m1 = ch1.weight, m2 = ch2.weight;
    Real a = m1*m2 + m2*m2;
    Real b = - (m1*m2*v1 + m2*m2*v2);
    Real c = -m1*m2*v2*v2 + m2*m2*v2*v2 + 2*m1*v1*m2*v2;

    double vn2 = (b + sqrt(b * b - a * c)) / a;
    double vn1 = (m1*v1 + m2*v2 - m2*vn2) / m1;

    // формирование результируещего вектора скорости
    ch1.speed.x = vn1 * cos(phi1);
    ch1.speed.y = vn1 * sin(phi1);
    ch2.speed.x = vn2 * cos(phi2);
    ch2.speed.y = vn2 * sin(phi2);

    return OK;
}
