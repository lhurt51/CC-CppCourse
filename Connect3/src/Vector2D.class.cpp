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
* Only need to connect verticle and horizontal
* Use a board of 5 by 6 with header for the column number
* Use ASCII graphics
*
******************************************************************************/

#include "Vector2D.class.hpp"

// Initialize the vector to 0, 0
Vector2D::Vector2D(void) : _x(0), _y(0) {
  return;
}

// Initializes the vector to be the int provided
Vector2D::Vector2D(int_fast32_t xy) : _x(xy), _y(xy) {
  return;
}

// Uses input to assign the values x, y as the vector
Vector2D::Vector2D(int_fast32_t x, int_fast32_t y) : _x(x), _y(y) {
  return;
}

// Copying another vector into this one
Vector2D::Vector2D(Vector2D const &src) {
  *this = src;
  return;
}

// Nothing to free
Vector2D::~Vector2D(void) {
  return;
}

int_fast32_t    Vector2D::getX(void) const {
	return this->_x;
}

int_fast32_t    Vector2D::getY(void) const {
	return this->_y;
}

void            Vector2D::setX(int_fast32_t x) {
	this->_x = x;
}

void            Vector2D::setY(int_fast32_t y) {
	this->_y = y;
}

Vector2D        &Vector2D::operator=(Vector2D const &rhs) {
	if (this != &rhs) {
		this->_x = rhs.getX();
		this->_y = rhs.getY();
	}
	return *this;
}

Vector2D        Vector2D::operator+(Vector2D const &rhs) const {
	return Vector2D(this->_x + rhs.getX(), this->_y + rhs.getY());
}

Vector2D        &Vector2D::operator+=(Vector2D const &rhs) {
    if (this != &rhs) {
        this->_x += rhs.getX();
        this->_y += rhs.getY();
    }
	return *this;
}

Vector2D        Vector2D::operator-(Vector2D const &rhs) const {
	return Vector2D(this->_x - rhs.getX(), this->_y - rhs.getY());
}

Vector2D        &Vector2D::operator-=(Vector2D const &rhs) {
    if (this != &rhs) {
        this->_x -= rhs.getX();
        this->_y -= rhs.getY();
    }
    return *this;
}

Vector2D        Vector2D::operator*(Vector2D const &rhs) const {
	return Vector2D(this->_x * rhs.getX(), this->_y * rhs.getY());
}

Vector2D        &Vector2D::operator*=(Vector2D const &rhs) {
    if (this != &rhs) {
        this->_x *= rhs.getX();
        this->_y *= rhs.getY();
    }
    return *this;
}

Vector2D        Vector2D::operator/(Vector2D const &rhs) const {
	return Vector2D(this->_x / rhs.getX(), this->_y / rhs.getY());
}

Vector2D        &Vector2D::operator/=(Vector2D const &rhs) {
    if (this != &rhs) {
        this->_x /= rhs.getX();
        this->_y /= rhs.getY();
    }
    return *this;
}

bool            Vector2D::operator>(Vector2D const &rhs) const {
    return (this->_x > rhs.getX() && this->_y > rhs.getY());
}

bool            Vector2D::operator<(Vector2D const &rhs) const {
    return (this->_x < rhs.getX() && this->_y < rhs.getY());
}

bool            Vector2D::operator>=(Vector2D const &rhs) const {
    return (this->_x >= rhs.getX() && this->_y >= rhs.getY());
}

bool            Vector2D::operator<=(Vector2D const &rhs) const {
    return (this->_x <= rhs.getX() && this->_y <= rhs.getY());
}

bool            Vector2D::operator==(Vector2D const &rhs) const {
	return (this->_x == rhs.getX() && this->_y == rhs.getY());
}

bool            Vector2D::operator!=(Vector2D const &rhs) const {
	return !(this->_x == rhs.getX() && this->_y == rhs.getY());
}

std::ostream    &operator<<(std::ostream &o, Vector2D const &i) {
	return o << "Vector2D (" << i.getX() << "," << i.getY() << ")";
}
