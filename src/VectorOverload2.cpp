#ifndef VECTOR_OVERLOAD_H
#define VECTOR_OVERLOAD_H

#include <raylib.h>
#include "VectorOverload2.h"
#include <iostream>

//std::ostream& operator<<(std::ostream& os, const std::vector<Vector2>& vv2) {
//    for (int i = 0; i < vv2.size(); i++) {
//        os << vv2 << "\n";
//    }
//    return os;
//}


//////////////////
// std::vector<Vector2>-float
// 
std::vector<Vector2> operator*(const std::vector<Vector2>& lhs, const float& rhs) {
    std::vector<Vector2> res = lhs;
    res *= rhs;
    return res; // uses the 
}
// NOTE(andai): no idea how vector division works
// Vector2 operator/(const Vector2& lhs, const Vector2& rhs){
//     return Vector2{lhs.x / rhs.x, lhs.y / rhs.y};
// }

//std::vector<Vector2> operator+(const std::vector<Vector2>& lhs, const float& rhs) {
//    std::vector<Vector2> res = lhs;
//    res += rhs;
//    return res;
//}
//
//std::vector<Vector2> operator-(const std::vector<Vector2>& lhs, const float& rhs) {
//    std::vector<Vector2> res = lhs;
//    res -= rhs;
//    return res;
//}


//////////////////
// std::vector<Vector2>-Vector
// 
// NOTE(andai): dot product because that's what XNA does
std::vector<Vector2> operator*(const std::vector<Vector2>& lhs, const Vector2& rhs) {
    std::vector<Vector2> res = lhs;
    res *= rhs;
    return res; // uses the 
}
// NOTE(andai): no idea how vector division works
// Vector2 operator/(const Vector2& lhs, const Vector2& rhs){
//     return Vector2{lhs.x / rhs.x, lhs.y / rhs.y};
// }

std::vector<Vector2> operator+(const std::vector<Vector2>& lhs, const Vector2& rhs) {
    std::vector<Vector2> res = lhs;
    res += rhs;
    return res;
}

std::vector<Vector2> operator-(const std::vector<Vector2>& lhs, const Vector2& rhs) {
    std::vector<Vector2> res = lhs;
    res -= rhs;
    return res;
}





///////////////////////////
// std::vector<Vector2>-float (in-place)

void operator*=(std::vector<Vector2>& lhs, const float& rhs) {
    for (int i = 0; i < lhs.size(); i++) {
        lhs[i].x *= rhs;
        lhs[i].y *= rhs;
    }
}

//void operator+=(std::vector<Vector2>& lhs, const float& rhs) {
//    for (int i = 0; i < lhs.size(); i++) {
//        lhs[i].x += rhs;
//        lhs[i].y += rhs;
//    }
//}
//
//void operator-=(std::vector<Vector2>& lhs, const float& rhs) {
//    for (int i = 0; i < lhs.size(); i++) {
//        lhs[i].x -= rhs;
//        lhs[i].y -= rhs;
//    }
//}



///////////////////////////
// std::vector<Vector2>-Vector (in-place)

void operator*=(std::vector<Vector2>& lhs, const Vector2& rhs) {
    for (int i = 0; i < lhs.size(); i++) {
        lhs[i].x *= rhs.x;
        lhs[i].y *= rhs.y;
    }
}

void operator+=(std::vector<Vector2>& lhs, const Vector2& rhs) {
    for (int i = 0; i < lhs.size(); i++) {
        lhs[i].x += rhs.x;
        lhs[i].y += rhs.y;
    }
}

void operator-=(std::vector<Vector2>& lhs, const Vector2& rhs) {
    for (int i = 0; i < lhs.size(); i++) {
        lhs[i].x -= rhs.x;
        lhs[i].y -= rhs.y;
    }
}




#endif // header guard