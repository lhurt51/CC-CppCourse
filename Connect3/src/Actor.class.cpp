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

#include "Actor.class.hpp"
#include "Game.class.hpp"

Actor::Actor(Vector2D pos, char const sprite) : _bCanDraw(false), _pos(pos), _sprite(sprite) {
	return;
}

Actor::Actor(Actor const &src) : _sprite(src.getSprite()) {
	*this = src;
	return;
}

Actor::~Actor(void) {
	_clear();
	return;
}

Actor 	&Actor::operator=(Actor const &rhs) {
	if (this != &rhs) {
		this->_bCanDraw = rhs.getCanDraw();
		this->_pos = rhs.getPos();
		(char&)this->_sprite = rhs.getSprite();
	}
	return *this;
}

bool		Actor::getCanDraw(void) const {
	return this->_bCanDraw;
}

Vector2D	Actor::getPos(void) const {
	return this->_pos;
}

char		Actor::getSprite(void) const {
	return this->_sprite;
}

void 		Actor::setPos(Vector2D pos) {
	_clear();
	this->_pos = pos;
	_checkPos();
	if (_bCanDraw) _draw();
}

void		Actor::setCanDraw(bool bCanDraw) {
	if (this->_bCanDraw == bCanDraw) return;
	this->_bCanDraw = bCanDraw;
}

bool		Actor::move(Vector2D dst) {
	if (dst == Vector2D(0, 0)) return false;
	_clear();
	_pos += dst;
	_checkPos();
	if (_bCanDraw) _draw();
	return true;
}

void		Actor::redraw(void) {
	_clear();
	_checkPos();
	if (_bCanDraw) _draw();
}

void 		Actor::_draw(void) const {
	chtype c;

	c = mvwinch(Game::getWindow(), this->_pos.getY(), _pos.getX());
	if ((char)c == this->_sprite) return;
	mvaddch(this->_pos.getY(), this->_pos.getX(), this->_sprite);
}

void 		Actor::_clear(void) const {
	chtype c;

	c = mvwinch(Game::getWindow(), this->_pos.getY(), _pos.getX());
	if ((char)c != this->_sprite) return;
	mvaddch(this->_pos.getY(), this->_pos.getX(), ' ');
}

std::ostream	&operator<<(std::ostream &o, Actor const &i) {
	return o << "Actor Info:" << std::endl <<
	"pos: " << i.getPos() << std::endl <<
	"sprite: " << i.getSprite() << std::endl;
}
