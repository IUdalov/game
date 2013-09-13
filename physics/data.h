#ifndef DATA_H
#define DATA_H

#include <vector>

#include "param.h"

class Checker {
    friend function Clash;
private:
    int spring;        // эластичность
    int weight;         // вес
    std::vector<int> speed;
    int radius;         // радиус шашки
    int rub;            //  трение

public:
    Checker() : spring(Spring::normal), weight(Weight::normal), rub(Rub::normal), radius(Radius::normal), speed({0, 0}) {
    }


};

class Wall {
    friend function Clash;
private:
    int spring;
    size_t state;
};

#endif // DATA_H
