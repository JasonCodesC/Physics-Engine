#pragma once
#include "Vector2.h"

class Ball {
public:
    Ball(float radius, float mass, const Vector2& pos);
    void applyForce(const Vector2& f);
    void applyImpulse(const Vector2& impulse);
    void integrate(float dt);
    void setPosition(const Vector2& p);
    void setVelocity(const Vector2& v);
    
    const Vector2& getPosition() const;
    const Vector2& getVelocity() const;
    float getRadius() const;
    float getMass() const;
    

private:
    Vector2 position;
    Vector2 velocity;
    Vector2 accumulatedForces;
    float mass;
    float radius;
};
