#pragma once
#include <cmath>

// Vectorized operations
struct Vector2 {
    float x, y;

    constexpr Vector2(float _x = 0, float _y = 0) : x(_x), y(_y) {}

    // Vector addition and subtraction
    [[nodiscard]] constexpr Vector2 operator+(const Vector2& o) const { return {x + o.x, y + o.y}; }
    [[nodiscard]] constexpr Vector2 operator-(const Vector2& o) const { return {x - o.x, y - o.y}; }

    // Vector multiplication and division
    [[nodiscard]] constexpr Vector2 operator*(float s) const { return {x * s, y * s}; }
    [[nodiscard]] constexpr Vector2 operator/(float s) const { return {x / s, y / s}; }

    // Shorthand addition
    constexpr Vector2& operator+=(const Vector2& o) { x += o.x; y += o.y; return *this; }

    // Dot Product
    [[nodiscard]] constexpr float dot(const Vector2& o) const { return x * o.x + y * o.y; }

    // Vector Length
    [[nodiscard]] inline float length() const { return std::sqrt(x * x + y * y); }

    // L2 Norm
    [[nodiscard]] constexpr float lengthSquared() const { return x * x + y * y; }

    // Normalizes to a unit vector
    [[nodiscard]] inline Vector2 normalized() const {
        float len = length();
        if (len > 0) {
            return Vector2(x / len, y / len);
        }
        return Vector2(0.0f);
    }

    // Negation, changes the direction
    [[nodiscard]] constexpr Vector2 operator-() const {
        return Vector2(-x, -y);
    }
};
