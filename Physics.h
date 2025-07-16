#pragma once
#include <vector>
#include "Ball.h"
#include "Vector2.h"

class Physics {
public:
    Physics(const Vector2& gravity, float worldW, float worldH);

    void addBall(Ball* b);
    void step(float dt);

    [[nodiscard]] const std::vector<Ball*>& getBalls() const { return balls; }

private:
    Vector2 gravity;
    float worldWidth, worldHeight;
    std::vector<Ball*> balls;
};
