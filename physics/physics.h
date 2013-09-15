#ifndef CLASH_H
#define CLASH_H

#include <math.h>
#include "data.h"

//я пока не в состоянии написать математику надо над ней подумать
// TO DECIDE
inline double ToRad( T phi ) {
    return ( ( phi % 361 ) / 180 * 3.1416 );
}

Error Clash(Wall& w, Checker& ch) {
    ch.speed.setX(ch.speed.x() * ch.spring / base * w.spring / base );
    ch.speed.setY(ch.speed.y() * ch.spring / base * w.spring / base );

    switch (w.phi) {
    case State::horizontal:
        ch.speed.setY(-ch.speed.y());
        break;
    case State::vertical:
        ch.speed.setX(-ch.speed.x());
        break;
    default:
        //assert(false);
        ;
    }

    return OK;
}

// работает
Error Move(Checker& ch, T time) {
    ch.speed.setX(ch.speed.x() * base / (ch.rub * ch.weight / (baseRub + 1)));
    ch.speed.setY(ch.speed.y() * base / (ch.rub * ch.weight / (baseRub + 1)));

    ch.coord.setX( ch.coord.x() + time * ch.speed.x() / base / baseTime);
    ch.coord.setY( ch.coord.y() + time * ch.speed.y() / base / baseTime);
    return OK;
}

#endif // CLASH_H
