/******************************************************************************
* Programmer Name:
* Liam Hurt
*
* Date:
* 2/6/2019
*
* Assignment Requirement:
* - Ask the user to guess a whole number between 1 and 1000 or character 'A'
*   to 'Z'
* - Your program will try to find the number
* - Keep track of the number of guesses by the computer
* - Use Recursive one of two search techniques: linear search or binary search
*   or randomize guess of a number.
* - Use a template class so the program could be used for integer or character,
*   your test function within your class should run with integer first then a
*   character
* - Use a randomized random number or letter generator for the item to guess
* - Allow the computer to have only 15 guesses
* - Your game class will have two functions or methods: playTheGame and static
*   Test
* - Your game shall have two modes: automatic where the computer tries to guess
*   you number without any input from you (except for the guess number) and
*   manual mode where each guess of the computer requires your input of Higher,
*   Lower, Right
*
******************************************************************************/

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
ALL DO NOT ALLOW ME to IMPLEMENT IN CPP FOR SOME REASON
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
