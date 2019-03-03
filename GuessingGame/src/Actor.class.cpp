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

#include "Actor.class.hpp"
#include "Game.class.hpp"

unsigned int			Actor::actorCount = 0;

Actor::Actor(Vector2D pos, char const sprite) : _id(Actor::actorCount++), _bCanDraw(false), _bCanClear(false) _pos(pos), _sprite(sprite) {
	return;
}

Actor::Actor(Actor const &src) : _id(src.getId()), _sprite(src.getSprite()) {
	*this = src;
	return;
}

Actor::~Actor(void) {
	_draw();
	return;
}

Actor 	&Actor::operator=(Actor const &rhs) {
	if (this != &rhs) {
		(int&)this->_id = rhs.getId();
		this->_bCanDraw = rhs.getCanDraw();
		this->_bCanClear = rhs.getCanClear();
		this->_pos = rhs.getPos();
		(char&)this->_sprite = rhs.getSprite();
	}
	return *this;
}

int			Actor::getId(void) const {
	return this->_id;
}

bool		Actor::getCanDraw(void) const {
	return this->_bCanDraw;
}

bool		Actor::getCanClear(void) const {
	return this->_bCanClear;
}

Vector2D	Actor::getPos(void) const {
	return this->_pos;
}

char		Actor::getSprite(void) const {
	return this->_sprite;
}

void 		Actor::setPos(Vector2D pos) {
	this->_pos = pos;
	redraw();
}

void		Actor::setCanDraw(bool bCanDraw) {
	if (this->_bCanDraw == bCanDraw) return;
	this->_bCanDraw = bCanDraw;
}

void		Actor::setCanDraw(bool bCanDraw) {
	if (this->_bCanDraw == bCanClear) return;
	this->_bCanDraw = bCanClear;
	this->_bCanClear = false;
}

bool		Actor::move(Vector2D dst) {
	if (dst == Vector2D(0, 0)) return false;
	_pos += dst;
	redraw();
	return true;
}

void		Actor::redraw(void) {
	_checkPos();
	_draw();
}

void 		Actor::_draw(void) const {
	static Vector2D<uint_fast32_t> lastPos();

	if (lastPos == this->_pos) return;
	if ((char)mvwinch(Game::getWindow(), lastPos.y, lastPos.x) == _sprite) mvaddch(lastPos.y, lastPos.x, ' ');
	if (_bCanDraw && (char)mvwinch(Game::getWindow(), _pos.y, _pos.x) != _sprite) mvaddch(_pos.y, _pos.x, _sprite);
	lastPos = this->_pos;
}

std::ostream	&operator<<(std::ostream &o, Actor const &i) {
	return o << "Actor Info:" << std::endl <<
	"can draw: " << i.getCanDraw() << std::endl <<
	"can clear: " << i.getCanClear() << std::endl <<
	"pos: " << i.getPos() << std::endl <<
	"sprite: " << i.getSprite() << std::endl;
}
