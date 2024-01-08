#ifndef VECTOR_OVERLOAD_H
#define VECTOR_OVERLOAD_H

#include <raylib.h>
#include <iostream>
std::ostream& operator<<(std::ostream& os, const Vector2& v2);

// unary minus
Vector2 operator-(const Vector2& v);

////////////////
// Vector-Float

Vector2 operator*(const Vector2& lhs, const float& rhs);

Vector2 operator*(const float& lhs, const Vector2& rhs);

Vector2 operator/(const Vector2& lhs, const float& rhs);

//////////////////
// Vector-Float in-place

void operator*=(Vector2& lhs, const float& rhs);

//////////////////
// Vector-Vector

// NOTE(andai): dot product because that's what XNA does
Vector2 operator*(const Vector2& lhs, const Vector2& rhs);
// NOTE(andai): no idea how vector division works
// Vector2 operator/(const Vector2& lhs, const Vector2& rhs){
//     return Vector2{lhs.x / rhs.x, lhs.y / rhs.y};
// }

Vector2 operator+(const Vector2& lhs, const Vector2& rhs);

Vector2 operator-(const Vector2& lhs, const Vector2& rhs);

///////////////////////////
// Vector-Vector in-place

void operator*=(Vector2& lhs, const Vector2& rhs);

void operator+=(Vector2& lhs, const Vector2& rhs);

void operator-=(Vector2& lhs, const Vector2& rhs);




#endif // header guard