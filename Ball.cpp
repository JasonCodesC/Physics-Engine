#include "Ball.h"
#include <cassert>

Ball::Ball(float r, float m, const Vector2& pos)
 : position(pos), velocity(0,0), accumulatedForces(0,0), mass(m>0?m:1.0f), radius(r) {}

void Ball::applyForce(const Vector2& f) {
    accumulatedForces += f;
}

void Ball::applyImpulse(const Vector2& impulse) {
    velocity += impulse / mass;
}

void Ball::integrate(float dt) {
    assert(dt > 0);
    Vector2 acc = accumulatedForces / mass;
    velocity += acc * dt;
    position += velocity * dt;
    accumulatedForces = Vector2(0,0);
}

void Ball::setPosition(const Vector2& p) { position = p; }
void Ball::setVelocity(const Vector2& v) { velocity = v; }

const Vector2& Ball::getPosition() const { return position; }
const Vector2& Ball::getVelocity() const { return velocity; }
float Ball::getRadius() const { return radius; }
float Ball::getMass() const { return mass; }
