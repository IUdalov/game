#ifdef DATA_H
#define DATA_H

#include "param.h"

struct Vect {
public:
    Real x, y;
public:
    Vect(Real _x = 0, Real _y = 0) : x(_x), y(_y) {
    }
};

struct Checker {
public:
    Vect coord;
    Vect speed;
    Real spring;         // упругость
    Real weight;         // вес
    Real rub;            //  трение

public:
    Checker(Vect _coord = Vect(0, 0), Vect _speed = Vect(0, 0), Real _weight = 0, Real _spring = 0, Real _rub = 0)
        : coord(_coord), speed(_speed), spring(_spring),
          weight(_weight), rub(_rub) {
    }
    Checker(const Checker& init)
        : coord(init.coord), speed(init.speed), spring(init.spring),
          weight(init.weight), rub(init.rub) {
    }

};

struct Wall {
public:
    Real spring;
    Real phi;
public:
    Wall(Real _spring = 0, Real _state = 0) : spring(_spring), phi(_state) {
    }
    Wall(const Wall& init) : spring(init.spring), phi(init.phi) {
    }
};

#endif // DATA_H
