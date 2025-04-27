#pragma once
#include "Ball.h"

class Collision {
    public:
    bool detect(const Ball& a, const Ball& b);
    void resolve(Ball& a, Ball& b, float restitution = 1.0f);
};
