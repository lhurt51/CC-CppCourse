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

#include <ncurses.h>
#include "Actor.class.hpp"

Actor::Actor(Vector2D pos, char const sprite) : _pos(pos), _sprite(sprite), _bCollided(false) {
	return;
}

Actor::Actor(Actor const &src) : _sprite(src.getSprite()) {
	*this = src;
	return;
}

Actor::~Actor(void) {
	this->clear();
	return;
}

Actor 	&Actor::operator=(Actor const &rhs) {
	if (this != &rhs) {
		this->_pos = rhs.getPos();
		this->_bCollided = rhs.getBCollided();
	}
	return *this;
}

Vector2D	Actor::getPos(void) const {
	return this->_pos;
}

char		Actor::getSprite(void) const {
	return this->_sprite;
}

bool		Actor::getBCollided(void) const {
	return this->_bCollided;
}

bool 		Actor::setPos(Vector2D pos) {
	if (this->_pos == pos) return false;
	else this->_pos = pos;
	return true;
}

bool		Actor::bDoesCollide(Actor &src) {
	if (this->_pos == src.getPos()) return true;
	return false;
}

bool		Actor::move(Vector2D dst) {
	if (dst == Vector2D(0, 0)) return false;
	else this->_pos += dst;
	return true;
}

void 		Actor::draw(void) {
	mvaddch(this->_pos.getY(), this->_pos.getX(), this->_sprite);
}

void 		Actor::clear(void) {
	mvaddch(this->_pos.getY(), this->_pos.getX(), ' ');
}

void		Actor::_hasCollided(void) {
	this->_bCollided = true;
}

std::ostream	&operator<<(std::ostream &o, Actor const &i) {
	return o << "Actor Info:" << std::endl <<
	"pos: " << i.getPos() << std::endl <<
	"sprite: " << i.getSprite() << std::endl <<
	"has collided: " << i.getBCollided() << std::endl;
}
