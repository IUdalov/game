#ifndef DATA_H
#define DATA_H

#include "param.h"

struct Vect {
public:
    Real x, y;
public:
    Vect(Real _x = 0, Real _y = 0) : x(_x), y(_y) {
    }
};

struct PhChecker {
public:
    Vect coord;
    Vect speed;
    Real spring;         // упругость
    Real weight;         // вес
    Real rub;            //  трение
    Real angle;
    Real angle_speed;
    Real radius;

public:
    PhChecker(Vect _coord = Vect(0, 0), Vect _speed = Vect(0, 0), Real _weight = 0,
              Real _spring = 0, Real _rub = 0, Real _angle = 0, Real _angle_speed = 0, Real _radius = 0)
        : coord(_coord), speed(_speed), spring(_spring),
          weight(_weight), rub(_rub), angle(_angle), angle_speed(_angle_speed), radius(_radius) {
    }
    PhChecker(const PhChecker& init)
        : coord(init.coord), speed(init.speed), spring(init.spring),
          weight(init.weight), rub(init.rub), angle(init.angle), angle_speed(init.angle_speed), radius(init.radius) {
    }

};

struct PhWall {
public:
    Real spring;
    Real phi;
public:
    PhWall(Real _spring = 0, Real _state = 0) : spring(_spring), phi(_state) {
    }
    PhWall(const PhWall& init) : spring(init.spring), phi(init.phi) {
    }
};

#endif // DATA_H
