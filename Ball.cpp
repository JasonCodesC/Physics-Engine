#include "Ball.h"
#include <cassert>

void Ball::applyForce(const Vector2& f) {
    accumulatedForces += f;
}

void Ball::applyImpulse(const Vector2& impulse) {
    if (mass > 0) { // Ensure mass is not zero to avoid division by zero
        velocity += impulse / mass;
    }
}

void Ball::integrate(float dt) {
    assert(dt > 0);
    if (mass > 0) { // Ensure mass is not zero
        Vector2 acc = accumulatedForces / mass;
        velocity += acc * dt;
    }
    position += velocity * dt;
    accumulatedForces = Vector2(0, 0);
}
