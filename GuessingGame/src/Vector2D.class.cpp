/******************************************************************************
* Programmer Name:
* Liam Hurt
*
* Date:
* 2/6/2019
*
* Assignment Requirement:
* Develop and test a connect - 4 like game except:
*
* Only need to connect 3
* There will be 3 players
* Only need to connect vertical and horizontal
* Use a board of 5 by 6 with header for the column number
* Use ASCII graphics
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

template<typename T>
Vector2D<T>         Vector2D<T>::operator-(void) const {
    return Vector2D<T>(-x, -y);
}

///-----------------------------VVVV
/* ALL DO NOT ALLOW ME to IMPLEMENT IN CPP FOR SOME REASON
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
*/

template class Vector2D<int>;
template class Vector2D<unsigned int>;
template class Vector2D<short>;
template class Vector2D<unsigned short>;
template class Vector2D<long>;
template class Vector2D<unsigned long>;
template class Vector2D<long long>;
template class Vector2D<unsigned long long>;
template class Vector2D<double>;
template class Vector2D<float>;
