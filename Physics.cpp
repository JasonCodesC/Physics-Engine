#include "Physics.h"
#include "Collisions.h"

Physics::Physics(const Vector2& g, float w, float h)
  : gravity(g), worldWidth(w), worldHeight(h) {}

void Physics::addBall(Ball* b) {
    balls.push_back(b);
}

void Physics::step(float dt) {
    //gravity
    for (auto b : balls)
        b->applyForce(gravity * b->getMass());

    //integrate
    for (auto b : balls)
        b->integrate(dt);

    //ball collisions. Not elastic
    const float restitutionBalls = 0.05f;
    Collision a;  
    for (size_t i = 0; i < balls.size(); ++i) {
        for (size_t j = i+1; j < balls.size(); ++j) {
            a.resolve(*balls[i], *balls[j], restitutionBalls);
        }
    }

    //wall collisions. Not elastic
    const float restitutionWall = 0.90f;
    for (auto b : balls) {
        Vector2 p = b->getPosition();
        Vector2 v = b->getVelocity();
        float r = b->getRadius();

        //left
        if (p.x - r < 0) {
            p.x = r;
            v.x = -v.x * restitutionWall;
        }
        //right
        if (p.x + r > worldWidth) {
            p.x = worldWidth - r;
            v.x = -v.x * restitutionWall;
        }
        //bottom
        if (p.y - r < 0) {
            p.y = r;
            v.y = -v.y * restitutionWall;
        }
        //top
        if (p.y + r > worldHeight) {
            p.y = worldHeight - r;
            v.y = -v.y * restitutionWall;
        }
        b->setPosition(p);
        b->setVelocity(v);
    }
}
