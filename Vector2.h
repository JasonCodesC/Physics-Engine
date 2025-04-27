#pragma once
#include <cmath>
//Vectorized operations
struct Vector2 {
    float x,y;
    Vector2(float _x=0, float _y=0): x(_x), y(_y) {}
    //Vector addition and subtraction
    Vector2 operator+(const Vector2& o) const { return {x+o.x, y+o.y}; }
    Vector2 operator-(const Vector2& o) const { return {x-o.x, y-o.y}; }
    //Vector multiplication and division
    Vector2 operator*(float s) const { return {x*s, y*s}; }
    Vector2 operator/(float s) const { return {x/s, y/s}; }
    //Shorthand addition
    Vector2& operator+=(const Vector2& o){ x+=o.x; y+=o.y; return *this; }
    //Dot Product
    float dot(const Vector2& o) const { return x*o.x + y*o.y; }
    //Vector Length
    float length() const { return std::sqrt(x*x + y*y); }
    //L2 Norm
    float lengthSquared() const { return x*x + y*y; }
    //Normalizes to a unit vector
    Vector2 normalized() const {
        float len = length();
        if (len > 0) {
            return Vector2(x / len, y / len);
        }
        return Vector2(0.0);
    }
    //Negation, changes the direction
    Vector2 operator-() const {
        return Vector2(-x, -y);
    }    
};
