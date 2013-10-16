#include "physics.h"

Real RoundConPi(Real phi) {
    return phi - 2 *M_PI * trunc(phi / (2 * M_PI));
}

// вроде работает, от скуки можно пооптимизировать
Error Move(PhChecker& ch, Real time) {

    // angle speed
    Real rub = ch.rub * ANGLE_RUB_COEF;
    if (fabs(ch.angle_speed) > rub ) {
        ch.angle_speed = ch.angle_speed > 0 ? ch.angle_speed - rub : ch.angle_speed + rub;
        ch.angle += ch.angle_speed * time;
    } else {
        ch.angle_speed = 0;
    }

    // line speed
    Real v = sqrt( pow( ch.speed.x, 2.) + pow( ch.speed.y, 2.) );
    if (v >= ch.rub) {
        v -= ch.rub;

        Real dir = ch.speed.x > 0 ? atan(ch.speed.y / ch.speed.x) : atan(ch.speed.y / ch.speed.x) + M_PI;

        ch.speed.x = v * cos(dir);
        ch.speed.y = v * sin(dir);

        ch.coord.x += ch.speed.x * time;
        ch.coord.y += ch.speed.y * time;

    } else {
        ch.speed.x = 0.;
        ch.speed.y = 0.;
    }

    return OK;
}

// с вращением не тестировалась
Error Clash(PhChecker& ch, PhWall& w) {

    ch.speed.x *= ch.spring * w.spring;
    ch.speed.y *= ch.spring * w.spring;

    // линейная скорость
    Real v = sqrt(pow(ch.speed.x, 2) + pow(ch.speed.y, 2));
    //Real phi = RoundConPi(_phi);

    Real ksi;
    if (fabs(ch.speed.x) > MIN_REAL) {
        ksi = atan(ch.speed.y / ch.speed.x);
    } else {
        ksi = 112358;
    }
    // над этим можно подумать
    Real dir = (ch.speed.x > 0) ? (2 * w.phi - ksi) : (2 * w.phi - (ksi + M_PI));

    ch.speed.x = v * cos(dir);
    ch.speed.y = v * sin(dir);

    // угловая скорость
    ch.angle_speed += (ch.speed.x * cos(w.phi) - ch.speed.y * sin(w.phi)) / ch.radius;
    return OK;
}

Error Clash(PhChecker& ch1, PhChecker& ch2) {

    Real spring = ch1.spring * ch2.spring;
    Real m1 = ch1.weight, m2 = ch2.weight;
    Real vx1 = ch1.speed.x;
    Real vy1 = ch1.speed.y;
    Real vx2 = ch2.speed.x;
    Real vy2 = ch2.speed.y;

    Real m21, dvx2, a, x21, y21, vx21, vy21, fy21, sign, vx_cm, vy_cm;

    m21 = m2 / m1;
    x21 = ch2.coord.x - ch1.coord.x;
    y21 = ch2.coord.y - ch1.coord.y;
    vx21 = vx2 - vx1;
    vy21 = vy2 - vy1;

    vx_cm = (m1 * vx1 + m2 * vx2) / (m1 + m2) ;
    vy_cm = (m1 * vy1 + m2 * vy2)/(m1 + m2) ;

    //     *** I have inserted the following statements to avoid a zero divide;
    //         (for single precision calculations,
    //          1.0E-12 should be replaced by a larger value). **************
    // так хитро избегоаем перехода через 0, захардкожени точность дабла
    fy21 = 1.0E-12 * fabs(y21);
    if ( fabs(x21) < fy21 ) {
        if (x21 < 0) { sign=-1; } else { sign=1;}
        x21=fy21 * sign;
    }

    //     ***  update velocities ***
    a = y21 / x21;
    dvx2 = -2 * (vx21 + a * vy21) / (( 1 + a * a) * (1 + m21));
    vx2 = vx2 + dvx2;
    vy2 = vy2 + a * dvx2;
    vx1 = vx1 - m21 * dvx2;
    vy1 = vy1 - a * m21 * dvx2;

    //     ***  velocity correction for inelastic collisions ***
    ch1.speed.x = (vx1 - vx_cm) * spring + vx_cm;
    ch1.speed.y = (vy1 - vy_cm) * spring + vy_cm;
    ch2.speed.x = (vx2 - vx_cm) * spring + vx_cm;
    ch2.speed.y = (vy2 - vy_cm) * spring + vy_cm;

    // угловая скорость
    Real tan_a = atan(a) + M_PI;
    Real point_on_circle = (ch1.speed.x - ch2.speed.x) * cos(tan_a) - (ch1.speed.y - ch2.speed.y) * sin(tan_a);
    ch1.angle_speed += point_on_circle / ch1.radius;
    ch2.angle_speed -= point_on_circle / ch2.radius;

    return OK;
}
