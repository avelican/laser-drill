#ifndef VECTOR_OVERLOAD_H
#define VECTOR_OVERLOAD_H

#include <raylib.h>
#include "VectorOverload.h"
#include <iostream>

std::ostream& operator<<(std::ostream& os, const Vector2& v2) {
    os << "Vector2{: " << v2.x << ", " << v2.y << "};" << "\n";
    return os;
}


// unary minus
//

Vector2 operator-(const Vector2& v) {
    return Vector2{ -v.x, -v.y };
}

////////////////
// Vector-Float

Vector2 operator*(const Vector2& lhs, const float& rhs){
    return Vector2{lhs.x * rhs, lhs.y * rhs};
}

Vector2 operator*(const float& lhs, const Vector2& rhs){
    return Vector2{rhs.x * lhs, rhs.y * lhs};
}

Vector2 operator/(const Vector2& lhs, const float& rhs){
    return Vector2{lhs.x / rhs, lhs.y / rhs};
}

//////////////////
// Vector-Float in-place

void operator*=(Vector2& lhs, const float& rhs) {
    lhs.x *= rhs;
    lhs.y *= rhs;
}

//////////////////
// Vector-Vector

// NOTE(andai): dot product because that's what XNA does
Vector2 operator*(const Vector2& lhs, const Vector2& rhs){
    return Vector2{lhs.x * rhs.x, lhs.y * rhs.y};
}
// NOTE(andai): no idea how vector division works
// Vector2 operator/(const Vector2& lhs, const Vector2& rhs){
//     return Vector2{lhs.x / rhs.x, lhs.y / rhs.y};
// }

Vector2 operator+(const Vector2& lhs, const Vector2& rhs){
    return Vector2{lhs.x + rhs.x, lhs.y + rhs.y};
}

Vector2 operator-(const Vector2& lhs, const Vector2& rhs){
    return Vector2{lhs.x - rhs.x, lhs.y - rhs.y};
}

///////////////////////////
// Vector-Vector in-place

void operator*=(Vector2& lhs, const Vector2& rhs) {
    lhs.x *= rhs.x;
    lhs.y *= rhs.y;
}

void operator+=(Vector2& lhs, const Vector2& rhs) {
    lhs.x += rhs.x;
    lhs.y += rhs.y;
}

void operator-=(Vector2& lhs, const Vector2& rhs) {
    lhs.x -= rhs.x;
    lhs.y -= rhs.y;
}




#endif // header guard