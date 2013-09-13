#ifndef CLASH_H
#define CLASH_H

#include <math.h>
#include "data.h"

inline int normalize(std::vector<int> v, int norm) {
    v[0] = (v[0] * norm) / 100;
    v[1] = (v[1] * norm) / 100;
    return 0;
}

int Clash(Wall w, Checkers ch) {

    return 0;
}

#endif // CLASH_H
