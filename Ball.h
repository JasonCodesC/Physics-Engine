#pragma once
#include "Vector2.h"

class Ball {
public:
    // Constructor
    constexpr Ball(float r, float m, const Vector2& pos)
        : position(pos), velocity(0, 0), accumulatedForces(0, 0), mass(m > 0 ? m : 1.0f), radius(r) {}

    // Apply force and impulse
    void applyForce(const Vector2& f);
    void applyImpulse(const Vector2& impulse);

    // Integrate motion
    void integrate(float dt);

    // Setters
    constexpr void setPosition(const Vector2& p) { position = p; }
    constexpr void setVelocity(const Vector2& v) { velocity = v; }

    // Getters
    [[nodiscard]] constexpr const Vector2& getPosition() const { return position; }
    [[nodiscard]] constexpr const Vector2& getVelocity() const { return velocity; }
    [[nodiscard]] constexpr float getRadius() const { return radius; }
    [[nodiscard]] constexpr float getMass() const { return mass; }

private:
    Vector2 position;
    Vector2 velocity;
    Vector2 accumulatedForces;
    float mass;
    float radius;
};
