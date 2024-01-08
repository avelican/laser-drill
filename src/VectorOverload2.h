#ifndef VECTOR_OVERLOAD_2_H
#define VECTOR_OVERLOAD_2_H

// NOTE(andai):  This one made me feel unclean,
//               so I made it a separate file...

#include <vector>
#include <raylib.h>
#include <raymath.h>

#include <iostream>

//std::ostream& operator<<(std::ostream& os, const std::vector<Vector2>& v2);

//////////////////
// std::vector<Vector2>-float
// 
std::vector<Vector2> operator*(const std::vector<Vector2>& lhs, const float& rhs);

//////////////////
// std::vector<Vector2>-float (in place)
// 
void operator*=(std::vector<Vector2>& lhs, const float& rhs);



//////////////////
// std::vector<Vector2>-Vector

// NOTE(andai): dot product because that's what XNA does
Vector2 operator*(std::vector<Vector2>& lhs, const Vector2& rhs);
// NOTE(andai): no idea how vector division works
// Vector2 operator/(const Vector2& lhs, const Vector2& rhs){
//     return Vector2{lhs.x / rhs.x, lhs.y / rhs.y};
// }

Vector2 operator+(std::vector<Vector2>& lhs, const Vector2& rhs);

Vector2 operator-(std::vector<Vector2>& lhs, const Vector2& rhs);


// std::vector<Vector2>-Vector (in-place)

void operator*=(std::vector<Vector2>& lhs, const Vector2& rhs);

void operator+=(std::vector<Vector2>& lhs, const Vector2& rhs);

void operator-=(std::vector<Vector2>& lhs, const Vector2& rhs);


#endif // header guard