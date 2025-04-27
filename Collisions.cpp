#include "Collisions.h"
#include "Ball.h"
#include <cmath>

//detects collisions
bool Collision::detect(const Ball& A, const Ball& B) {
    float dist2 = (A.getPosition() - B.getPosition()).lengthSquared();
    float radSum = A.getRadius() + B.getRadius();
    return dist2 < (radSum * radSum);
}

//resolves the collisions
void Collision::resolve(Ball& A, Ball& B, float e) {
    if (!detect(A,B)) {
        return;
    }
    Vector2 n = (B.getPosition() - A.getPosition()).normalized();
    float relVel = (B.getVelocity() - A.getVelocity()).dot(n);
    if (relVel > 0) {
        return;
    }
    float j = -(1 + e) * relVel / (1/A.getMass() + 1/B.getMass());
    Vector2 impulse = n * j;
    A.applyImpulse(impulse -0.40f);
    B.applyImpulse( impulse * 0.40f);
}
