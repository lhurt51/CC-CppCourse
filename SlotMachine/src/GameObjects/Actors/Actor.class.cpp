/*******************************************************************************\
* Programmer Name:																*
* Liam Hurt																		*
*																				*
* Date:																			*
* 3/28/2019																		*
*																				*
* Assignment Requirement:														*
* This program will play a slot machine game. The slot machine shall have 3     *
* slots (or a single number between 0 to 9 for each slot) of the following      *
* ASCII number vector to use (see below). The user shall have the ability to    *
* make a bet and then the game will automatically spin the digits. Use a delay  *
* to simulate the numbers changing before the final numbers are revealed (if    *
* you use C++ 11 see the function below). The following conditions will be      *
* programmed:                                                                   *
*                                                                               *
* 3 matching numbers win 10 times the bet                                       *
*                                                                               *
* 2 matching numbers win 5 times the bet                                        *
*                                                                               *
* no matching number losses the bet				                     			*
*																				*
\*******************************************************************************/

#include "Vector2D.class.hpp"
#include "Actor.class.hpp"
#include "GameEngine.class.hpp"

// Default constructor
Actor::Actor(Vector2D<uint_fast32_t> pos, std::string const sprite) : GameObject(pos, sprite), _bCanClear(false), _bNeedsUpdate(true) {
	return;
}

// Copy constructor
Actor::Actor(Actor const &src) : GameObject(src) {
	*this = src;
	return;
}

// Default deconstructor
Actor::~Actor(void) {
	return;
}

// Equal sign overload
Actor					&Actor::operator=(Actor const &rhs) {
	if (this != &rhs) {
		this->_bCanClear = rhs.getCanClear();
		this->_bNeedsUpdate = rhs.getNeedsUpdate();
	}
	return *this;
}

// Getters --
bool					Actor::getCanClear(void) const {
	return this->_bCanClear;
}

bool					Actor::getNeedsUpdate(void) const {
	return this->_bNeedsUpdate;
}

// Setters --
void					Actor::setCanClear(void) {
	if (this->_bCanClear)
		this->_bCanClear = false;
}

// Sett needs update for
void					Actor::setNeedsUpdate(void) {
	if (this->_bNeedsUpdate)
		this->_bNeedsUpdate = false;
}

void 					Actor::setPos(Vector2D<uint_fast32_t> pos) {
	pos = GameEngine::checkGameObjectPos(pos, _sprite);
	if (this->_pos != pos) {
		this->_pos = pos;
		_bNeedsUpdate = true;
	}
}

// Set a new sprite for dynamic actors
void					Actor::setSprite(std::string sprite) {
	if (this->_sprite == sprite) return;
	(std::string&)this->_sprite = sprite;
	_bNeedsUpdate = true;
}

// Output overload for testing
std::ostream			&operator<<(std::ostream &o, Actor const &i) {
	return o << "Actor Info:" << std::endl <<
	"can clear: " << i.getCanClear() << std::endl <<
	"needs update: " << i.getNeedsUpdate() << std::endl;
}
