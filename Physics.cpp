#include "Physics.h"
#include "Collisions.h"

Physics::Physics(const Vector2& g, float w, float h)
  : gravity(g), worldWidth(w), worldHeight(h) {}

void Physics::addBall(Ball* b) {
    balls.push_back(b);
}

void Physics::step(float dt) {
    // Apply gravity and integrate
    for (auto b : balls) {
        b->applyForce(gravity * b->getMass());
        b->integrate(dt);
    }

    // Ball-ball collisions
    const float restitutionBalls = 0.8f; // Slightly more realistic restitution
    for (size_t i = 0; i < balls.size(); ++i) {
        for (size_t j = i + 1; j < balls.size(); ++j) {
            Collision::resolve(*balls[i], *balls[j], restitutionBalls);
        }
    }

    // Wall collisions
    const float restitutionWall = 0.90f;
    for (auto b : balls) {
        Vector2 p = b->getPosition();
        Vector2 v = b->getVelocity();
        const float r = b->getRadius();

        if (p.x - r < 0) {
            p.x = r;
            v.x = -v.x * restitutionWall;
        } else if (p.x + r > worldWidth) {
            p.x = worldWidth - r;
            v.x = -v.x * restitutionWall;
        }

        if (p.y - r < 0) {
            p.y = r;
            v.y = -v.y * restitutionWall;
        } else if (p.y + r > worldHeight) {
            p.y = worldHeight - r;
            v.y = -v.y * restitutionWall;
        }
        b->setPosition(p);
        b->setVelocity(v);
    }
}
