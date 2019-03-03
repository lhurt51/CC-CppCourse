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

#include "Player.class.hpp"

Player::Player(void) : Actor(Vector2D<uint_fast32_t>(DEFAULT_SPAWN), ' '), bCanInput(true), _bExitReq(false), _bIsTyping(false) {
	return;
}

Player::Player(Player const &src) : Actor(src) {
	*this = src
	return;
}

Player::~Player(void) {
	return;
}

// Overload operators --
Player&				Player::operator=(Player const &rhs) {
	if (this != &rhs) {
		this->_bCanInput = rhs.getCanInput();
		this->_bExitReq = rhs.getExitReq();
		this->_bIsTyping = rhs.getIsTyping();
	}
	return *this;
}

// Getters --
bool				Player::getCanInput(void) const {
	return this->_bCanInput;
}

bool				Player::getExitReq(void) const {
	return this->_bExitReq;
}

bool				Player::getIsTyping(void) const {
	return this->_bIsTyping;
}

// Setters --
void				Player::setCanInput(bool bCanInput) {
	if (this->_bCanInput == bCanInput) return;
	this->_bCanInput = bCanInput;
}

void				Player::setExitReq(bool bExitReq) {
	if (this->_bExitReq == bExitReq) return;
	this->_bExitReq = bExitReq;
}

void				Player::setIsTyping(bool bIsTyping) {
	if (this->_bIsTyping == bIsTyping) return;
	this->_bIsTyping = bIsTyping;
}

// Overloaded Public Actor Methods --
void				Player::tick(void) {

}

// Overloaded Protected Actor Methods --
void				Player::_checkPos(void) {
	Vector2D<uint_fast32_t> default(DEFAULT_SPAWN);
	
	if (_pos != default) _pos = default;
}

// Handle the users input
void				Player::_handleUserInput(int input) {

}
