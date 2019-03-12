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
#include "MenuItem.class.hpp"

// Default constructors to initialize the pos and sprite
MenuItem::MenuItem(Vector2D<uint_fast32_t> const pos, std::string const &sprite) : Actor(pos, sprite), _bIsSelected(false), _bShouldExec(false) {
	return;
}

// Copy constructor
MenuItem::MenuItem(MenuItem const &src) : Actor(src) {
	*this = src;
	return;
}

// Deconstructor
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
