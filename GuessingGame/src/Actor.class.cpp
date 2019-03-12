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

#include <typedefs.hpp>
#include "Vector2D.class.hpp"
#include "Actor.class.hpp"
#include "GameEngine.class.hpp"
#include "MenuItem.class.hpp"

std::vector<Actor*>		Actor::_allActors;

Actor::Actor(Vector2D<uint_fast32_t> pos, std::string const sprite) : _bCanDraw(false), _bCanClear(false), _bNeedsUpdate(true), _pos(pos), _sprite(sprite) {
	Actor::addActor(this);
	return;
}

Actor::Actor(Actor const &src) : _sprite(src.getSprite()) {
	*this = src;
	return;
}

Actor::~Actor(void) {
	Actor::removeActor(this);
	return;
}

Actor					&Actor::operator=(Actor const &rhs) {
	if (this != &rhs) {
		this->_bCanDraw = rhs.getCanDraw();
		this->_bCanClear = rhs.getCanClear();
		this->_bNeedsUpdate = rhs.getNeedsUpdate();
		this->_pos = rhs.getPos();
		(std::string&)this->_sprite = rhs.getSprite();
	}
	return *this;
}

int						Actor::getThisIndexInAllActors(void) {
	return Actor::findActorIndex(this);
}

bool					Actor::getCanDraw(void) const {
	return this->_bCanDraw;
}

bool					Actor::getCanClear(void) const {
	return this->_bCanClear;
}

bool					Actor::getNeedsUpdate(void) const {
	return this->_bNeedsUpdate;
}

Vector2D<uint_fast32_t>	Actor::getPos(void) const {
	return this->_pos;
}

std::string	const		Actor::getSprite(void) const {
	return this->_sprite;
}

void 					Actor::setPos(Vector2D<uint_fast32_t> pos) {
	this->_pos = pos;
	this->_bNeedsUpdate = true;
}

void					Actor::setCanDraw(bool bCanDraw) {
	if (this->_bCanDraw == bCanDraw) return;
	this->_bCanDraw = bCanDraw;
	this->_bNeedsUpdate = true;
}

void					Actor::setCanClear() {
	this->_bCanClear = true;
	this->_bCanDraw = false;
	this->_bNeedsUpdate = true;
}

void					Actor::resetNeedsUpdate(void) {
	this->_bNeedsUpdate = false;
}

std::vector<Actor*>		Actor::getAllActors(void) {
	return Actor::_allActors;
}

void					Actor::removeActors(void) {
	for (unsigned i = 0; i < Actor::_allActors.size(); i++) {
		if (Actor::_allActors[i]->getCanClear()) {
			Actor::_allActors.erase(Actor::_allActors.begin() + i);
		}
	}
}

void					Actor::tickAllActors(void) {
	for (unsigned i = 0; i < Actor::_allActors.size(); i++) {
		Actor::_allActors[i]->tick();
	}
}

void					Actor::printAllActors(void) {
	for (unsigned i = 0; i < Actor::_allActors.size(); i++) {
		MenuItem* temp = (MenuItem*)Actor::_allActors[i];
		if (temp && temp->getIsSelected()) GameEngine::useMenuAttr(true);
		if (Actor::_allActors[i]->getCanDraw())
			GameEngine::printPos(Actor::_allActors[i]->getPos(), Actor::_allActors[i]->getSprite());
		GameEngine::useMenuAttr(false);
	}
}

Actor*					Actor::getActor(unsigned index) {
	if (index >= Actor::_allActors.size()) return nullptr;
	return Actor::_allActors[index];
}

int						Actor::findActorIndex(Actor *actor) {
	for (unsigned i = 0; i < Actor::_allActors.size(); i++) {
		if (Actor::_allActors[i] == actor) return i;
	}
	return -1;
}

void					Actor::addActor(Actor *actor) {
	Actor::_allActors.push_back(actor);
}

void					Actor::removeActor(Actor *actor) {
	for (unsigned i = 0; i < Actor::_allActors.size(); i++) {
		if (Actor::_allActors[i] == actor)
			Actor::_allActors.erase(Actor::_allActors.begin() + i);
	}
}

void					Actor::setAllActorsCanDraw(bool bCanDraw) {
	for (unsigned i = 0; i < Actor::_allActors.size(); i++) {
		Actor::_allActors[i]->setCanDraw(bCanDraw);
	}
}

void					Actor::setActorCanDraw(unsigned index, bool bCanDraw) {
	if (index >= Actor::_allActors.size()) return;
	Actor::_allActors[index]->setCanDraw(bCanDraw);
}

void					Actor::setAllActorsCanClear() {
	for (unsigned i = 0; i < Actor::_allActors.size(); i++) {
		Actor::_allActors[i]->setCanClear();
	}
}

void					Actor::setActorCanClear(unsigned index) {
	if (index >= Actor::_allActors.size()) return;
	Actor::_allActors[index]->setCanClear();
}

void					Actor::resetAllActorsNeedsUpdate() {
	for (unsigned i = 0; i < Actor::_allActors.size(); i++) {
		Actor::_allActors[i]->resetNeedsUpdate();
	}
}

void					Actor::resetActorNeedsUpdate(unsigned index) {
	if (index >= Actor::_allActors.size()) return;
	Actor::_allActors[index]->resetNeedsUpdate();
}

bool					Actor::anyActorNeedsUpdate(void) {
	for (unsigned i = 0; i < Actor::_allActors.size(); i++) {
		if (Actor::_allActors[i]->getNeedsUpdate()) return true;
	}
	return false;
}

std::ostream			&operator<<(std::ostream &o, Actor const &i) {
	return o << "Actor Info:" << std::endl <<
	"can draw: " << i.getCanDraw() << std::endl <<
	"can clear: " << i.getCanClear() << std::endl <<
	"pos: " << i.getPos() << std::endl <<
	"sprite: " << i.getSprite() << std::endl;
}
