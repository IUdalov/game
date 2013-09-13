#ifndef PARAM_H
#define PARAM_H

enum Spring {
    inert = 0,
    soft = 50,
    normal = 100,
    power = 150,
    superpower = 200
};

enum Weight {
    low,
    normal,
    high
};

enum Rub {
    low,
    normal,
    high
};

enum Radius {
    low,
    normal,
    high
};

enum State {
    vertical = 90,
    horizontal = 0,
    rotated = 45
};

#endif // PARAM_H
