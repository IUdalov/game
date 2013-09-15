#ifndef CLASH_H
#define CLASH_H

#include <math.h>
#include "data.h"

// работает
Error Move(Checker& ch, T time) {
    ch.speed.setX(ch.speed.x() * base / (ch.rub * ch.weight / (baseRub + 1)));
    ch.speed.setY(ch.speed.y() * base / (ch.rub * ch.weight / (baseRub + 1)));

    ch.coord.setX( ch.coord.x() + time * ch.speed.x() / base / baseTime);
    ch.coord.setY( ch.coord.y() + time * ch.speed.y() / base / baseTime);
    return OK;
}

// я пока не в состоянии написать математику надо над ней подумать, но то что здесь вроде длжно работать
// но нужно тестировать
Error Clash(Wall& w, Checker& ch) {
    ch.speed.setX(ch.speed.x() * ch.spring / base * w.spring / base );
    ch.speed.setY(ch.speed.y() * ch.spring / base * w.spring / base );

    // ЭТО ОЧЕНЬ МЕДЛЕННО
    double m_speed = sqrt(pow((ch.speed.x()), 2) + pow((ch.speed.y()), 2));
    double dir = 2*w.phi - atan( (double)ch.speed.x() / (double)ch.speed.x() );

    ch.speed.setX(round(m_speed * cos(dir)));
    ch.speed.setY(round(m_speed * sin(dir)));
    return OK;
}

// no
Error Clash(Checker& ch1, Checker& ch2) {

    return OK;
}

#endif // CLASH_H
