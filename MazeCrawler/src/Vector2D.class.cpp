/*******************************************************************************\
* Programmer Name:																*
* Liam Hurt																		*
*																				*
* Date:																			*
* 3/16/2019																		*
*																				*
* Assignment Requirement:														*
* 7.33 (Maze Traversal) The grid of hashes (#) and dots (.) in Fig. 7.29 is a	*
* two-dimensional builtin array representation of a maze. In the				*
* two-dimensional built-in array, the hashes represent the walls of the maze	*
* and the dots represent squares in the possible paths through the maze. Moves	*
* can be made only to a location in the built-in array that contains a dot.		*
* There is a simple algorithm for walking through a maze that guarantees to		*
* find the exit (assuming that there is an exit). If there is not an exit,		*
* you’ll arrive at the starting location again. Place your right hand on		*
* the wall to your right and begin walking forward. Never remove your hand		*
* from the wall. If the maze turns to the right, you follow the wall to the		*
* right. As long as you do not remove your hand from the wall, eventually		*
* you’ll arrive at the exit of the maze. There may be a shorter path than the	*
* one you’ve taken, but you are guaranteed to get out of the maze if you		*
* follow the algorithm.															*
*																				*
*  # # # # # # # # # # # #														*
*  # . . . # . . . . . . #														*
*  . . # . # . # # # # . #														*
*  # # # . # . . . . # . #														*
*  # . . . . # # # . # . .														*
*  # # # # . # . # . # . #														*
*  # . . # . # . # . # . #														*
*  # # . # . # . # . # . #														*
*  # . . . . . . . . # . #														*
*  # # # # # # . # # # . #														*
*  # . . . . . . # . . . #														*
*  # # # # # # # # # # # #														*
*																				*
* Write recursive function mazeTraverse to walk through the maze. The function	*
* should receive arguments that include a 12-by-12 built-in array of chars		*
* representing the maze and the starting location of the maze. As mazeTraverse	*
* attempts to locate the exit from the maze, it should place the character X	*
* in each square in the path. The function should display the maze after each	*
* move, so the user can watch as the maze is solved.							*
*																				*
\*******************************************************************************/

#include <cmath>
#include <cfloat>
#include <climits>
#include "Vector2D.class.hpp"

// Initialize the vector to 0, 0
template<typename T>
Vector2D<T>::Vector2D(void) : x(T(0)), y(T(0)) {
  return;
}

// Initializes the vector to be the int provided
template<typename T>
Vector2D<T>::Vector2D(const T& vxy) : x(vxy), y(vxy) {
  return;
}

// Uses input to assign the values x, y as the vector
template<typename T>
Vector2D<T>::Vector2D(const T& vx, const T& vy) : x(vx), y(vy) {
  return;
}

// Copying another vector into this one
template<typename T>
Vector2D<T>::Vector2D(const Vector2D& src) {
  *this = src;
  return;
}

// Overload operators --
template<typename T>
Vector2D<T>&        Vector2D<T>::operator=(const Vector2D& v) {
	if (this != &v) {
		x = v.x;
		y = v.y;
	}
	return *this;
}

template<typename T>
Vector2D<T>&        Vector2D<T>::operator+=(const Vector2D& v) {
    x += v.x;
    y += v.y;
	return *this;
}

template<typename T>
Vector2D<T>&        Vector2D<T>::operator-=(const Vector2D& v) {
    x -= v.x;
    y -= v.y;
    return *this;
}

template<typename T>
Vector2D<T>&        Vector2D<T>::operator*=(const Vector2D& v) {
    x *= v.x;
    y *= v.y;
    return *this;
}

template<typename T>
Vector2D<T>&        Vector2D<T>::operator/=(const Vector2D& v) {
    x /= v.x;
    y /= v.y;
    return *this;
}

template<typename T>
Vector2D<T>&        Vector2D<T>::operator*=(const T& s) {
    x *= s;
    y *= s;
    return *this;
}

template<typename T>
Vector2D<T>&        Vector2D<T>::operator/=(const T& s) {
    x /= s;
    y /= s;
    return *this;
}

/* Inline implementation so no need for the cpp
template<typename T>
Vector2D<T>         Vector2D<T>::operator-(void) const {
    return Vector2D<T>(-x, -y);
}

\\\-----------------------------VVVVVVVVV-----------------------------------///
IMPLEMENTED IN HPP FOR INLINE DECLARATION
template<typename T>
Vector2D<T>        operator+(const Vector2D<T> l, const Vector2D<T> r) {
  return Vector2D<T>(l) += r;
}

template<typename T>
Vector2D<T>               operator-(const Vector2D<T> l, const Vector2D<T> r) {
  return Vector2D<T>(l) -= r;
}

template<typename T>
Vector2D<T>               operator*(const Vector2D<T> l, const Vector2D<T> r) {
  return Vector2D<T>(l) *= r;
}

template<typename T>
Vector2D<T>               operator/(const Vector2D<T> l, const Vector2D<T> r) {
  return Vector2D<T>(l) /= r;
}

template<typename T>
Vector2D<T>               operator*(const T s, const Vector2D<T> v) {
  return Vector2D<T>(v) *= s;
}

template<typename T>
Vector2D<T>               operator*(const Vector2D<T> v, const T s) {
  return Vector2D<T>(v) *= s;
}

template<typename T>
Vector2D<T>               operator/(const T s, const Vector2D<T> v) {
  return Vector2D<T>(v) /= s;
}

template<typename T>
Vector2D<T>               operator/(const Vector2D<T> v, const T s) {
      return Vector2D<T>(v) /= s;
}
\\\-----------------------------^^^^^^^^^-----------------------------------///
*/


// Utility Functions
template<typename T>
T                         DotProduct(const Vector2D<T>& a, const Vector2D<T>& b) {
    return ((a.x * b.x) + (a.y + b.y));
}

template<typename T>
T                         CrossProduct(const Vector2D<T>& a, const Vector2D<T>& b) {
    return ((a.x * b.y) - (a.y * b.x));
}


template<typename T>
T                         EuclideanNorm(const Vector2D<T>& v) {
    return std::sqrt((v.x * v.x) + (v.y * v.y));
}

template<typename T>
Vector2D<T>               Normal(const Vector2D<T>& v) {
    float magnitude = EuclideanNorm(v);
    return Vector2D<T>(v.x / magnitude, v.y / magnitude);
}

template<typename T>
Vector2D<T>               Perpendicular(const Vector2D<T>& v) {
    return Vector2D<T>(v.y, -v.x);
}

template<typename T>
bool                      Inersect(const Vector2D<T>& line1A, const Vector2D<T>& line1B, const Vector2D<T>& line2A, const Vector2D<T>& line2B) {
    Vector2D<T> p = line1A;
    Vector2D<T> r = line1B - line1A;
    Vector2D<T> q = line2A;
    Vector2D<T> s = line2B - line2A;

    float t = CrossProduct((q - p), s) / CrossProduct(r, s);
    float u = CrossProduct((q - p), r) / CrossProduct(r, s);

    return (0.0 <= t && t <= 1.0) && (0.0 <= u && u <= 1.0);
}

template<typename T>
Vector2D<T>               GetInersect(const Vector2D<T>& line1A, const Vector2D<T>& line1B, const Vector2D<T>& line2A, const Vector2D<T>& line2B) {
    float pX = CrossProduct(line1A, line1B) * (line2A.x - line2B.x) -
                CrossProduct(line2A, line2B) * (line1A.x - line1B.x);
    float pY = CrossProduct(line1A, line1B) * (line2A.y - line2B.y) -
                CrossProduct(line2A, line2B) * (line1A.y - line1B.y);
    float denom = (line1A.x - line1B.x) * (line2A.y - line2B.y) -
                (line1A.y - line1B.y) * (line2A.x - line2B.x);
    return Vector2D<T>(pX / denom, pY / denom);
}
