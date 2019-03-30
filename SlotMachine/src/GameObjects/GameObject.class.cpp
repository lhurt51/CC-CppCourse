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
#include "GameObject.class.hpp"
#include "GameEngine.class.hpp"
#include "Handlers/GameObjectHandler.class.hpp"

// Default constructor
GameObject::GameObject(Vector2D<uint_fast32_t> pos, std::string const sprite) : _bCanDraw(true), _sprite(sprite) {
	setPos(pos);
	GameObjectHandler::addObject(this);
	return;
}

// Copy constructor
GameObject::GameObject(GameObject const &src) : _sprite(src.getSprite()) {
	*this = src;
	return;
}

// Default deconstructor
GameObject::~GameObject(void) {
	GameObjectHandler::removeObject(this);
	return;
}

// Equal sign overload
GameObject					&GameObject::operator=(GameObject const &rhs) {
	if (this != &rhs) {
		this->_bCanDraw = rhs.getCanDraw();
		this->_pos = rhs.getPos();
		(std::string&)this->_sprite = rhs.getSprite();
	}
	return *this;
}

// Getters --
bool					GameObject::getCanDraw(void) const {
	return this->_bCanDraw;
}

Vector2D<uint_fast32_t>	GameObject::getPos(void) const {
	return this->_pos;
}

std::string	const		GameObject::getSprite(void) const {
	return this->_sprite;
}

// Setters --
void					GameObject::setCanDraw(bool bCanDraw) {
	if (this->_bCanDraw != bCanDraw)
		this->_bCanDraw = bCanDraw;
}

void 					GameObject::setPos(Vector2D<uint_fast32_t> pos) {
	pos = GameEngine::checkGameObjectPos(pos, _sprite);
	if (this->_pos != pos)
		this->_pos = pos;
}

void 					GameObject::draw(void) {
	if(_bCanDraw) GameEngine::printPos(_pos, _sprite);
}

// Output pverload for testing
std::ostream			&operator<<(std::ostream &o, GameObject const &i) {
	return o << "GameObject Info:" << std::endl <<
	"can draw: " << i.getCanDraw() << std::endl <<
	"pos: " << i.getPos() << std::endl <<
	"sprite: " << i.getSprite() << std::endl;
}
