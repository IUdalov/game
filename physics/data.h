#ifndef DATA_H
#define DATA_H

#include <vector>
#include <QPoint>

#include "param.h"

class Checker {
public:
    T spring;         // упругость
    T weight;         // вес
    QPoint speed;
    QPoint coord;
    T rub;            //  трение

public:
    Checker()
        : spring(Spring::normal), weight(Weight::normal),
          speed(0, 0), coord(0, 0), rub(Rub::normal) {
    }
    Checker(QPoint _coord, QPoint _speed, T _weight, T _spring, T _rub = 0)
        : spring(_spring), weight(_weight), speed(_speed), coord(_coord),
          rub(_rub) {
    }
    Checker(const Checker& init)
        : spring(init.spring), weight(init.weight),
          speed(init.speed), coord(init.coord), rub(init.rub) {
    }

};

class Wall {
public:
    T spring;
    int phi;
public:
    Wall() : spring(Spring::normal), phi(State::vertical) {
    }
    Wall(T _spring, T _state) : spring(_spring), phi(_state) {
    }
    Wall(const Wall& init) : spring(init.spring), phi(init.phi) {
    }
};

#endif // DATA_H
