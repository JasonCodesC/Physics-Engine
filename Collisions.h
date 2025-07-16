#pragma once
#include "Ball.h"

namespace Collision {
    [[nodiscard]] inline bool detect(const Ball& a, const Ball& b) {
        const float dist2 = (a.getPosition() - b.getPosition()).lengthSquared();
        const float radSum = a.getRadius() + b.getRadius();
        return dist2 < (radSum * radSum);
    }

    inline void resolve(Ball& a, Ball& b, float restitution = 1.0f) {
        if (!detect(a, b)) {
            return;
        }

        const Vector2 n = (b.getPosition() - a.getPosition()).normalized();
        const float relVel = (b.getVelocity() - a.getVelocity()).dot(n);

        if (relVel > 0) {
            return; // Moving away
        }

        const float invMassA = 1.0f / a.getMass();
        const float invMassB = 1.0f / b.getMass();
        const float j = -(1.0f + restitution) * relVel / (invMassA + invMassB);
        const Vector2 impulse = n * j;

        a.applyImpulse(-impulse);
        b.applyImpulse(impulse);
    }
}
