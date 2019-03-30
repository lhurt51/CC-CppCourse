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
#include "MenuItem.class.hpp"
#include "GameEngine.class.hpp"

// Default constructors to initialize the pos and sprite
MenuItem::MenuItem(Vector2D<uint_fast32_t> const pos, std::string const &sprite) : Actor(pos, sprite), _bIsSelected(false), _bShouldExec(false) {
	return;
}

// Copy constructor
MenuItem::MenuItem(MenuItem const &src) : Actor(src) {
	*this = src;
	return;
}

// De-constructor
MenuItem::~MenuItem(void) {
	return;
}

// Overload equals operator
MenuItem		&MenuItem::operator=(MenuItem const &rhs) {
	if (this != &rhs) {
		this->_bIsSelected = rhs.getIsSelected();
		this->_bShouldExec = rhs.getShouldExec();
	}
	return *this;
}

// Getters --
bool			MenuItem::getIsSelected(void) const {
	return this->_bIsSelected;
}

bool			MenuItem::getShouldExec(void) const {
	return this->_bShouldExec;
}

// Setters --
void			MenuItem::setIsSelected(bool const bIsSelected) {
	if (this->_bIsSelected == bIsSelected) return;
	this->_bIsSelected = bIsSelected;
	this->_bNeedsUpdate = true;
}

void			MenuItem::setShouldExec(bool const bShouldExec) {
	if (!this->_bIsSelected) return;
	this->_bShouldExec = bShouldExec;
	this->_bNeedsUpdate = true;
}

// Actor abstract method implementation to execute code base on bShouldExec
void			MenuItem::tick(void) {
	if (_bShouldExec) {
		_execute();
		_bShouldExec = false;
	}
}

void 			MenuItem::draw(void) {
	if (_bIsSelected) GameEngine::useMenuItemAttr(true);
	GameObject::draw();
	if (_bIsSelected) GameEngine::useMenuItemAttr(false);
}
