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

Player::Player(void) : Actor(Vector2D<uint_fast32_t>(DEFAULT_SPAWN), ""), bCanInput(true), _bExitReq(false), _bIsTyping(false) {
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
		this->_bIsTyping = rhs.getIsTyping();
	}
	return *this;
}

// Getters --
bool				Player::getIsTyping(void) const {
	return this->_bIsTyping;
}

// Setters --
void				Player::startTyping(void) {
	this->_bIsTyping = true;
}

void				Player::stopTyping(void) {
	this->_bIsTyping = false;
}

void				moveRight(void) {
	_mRightPressed = true;
}

void				stopRight(void) {
	_mRightPressed = false;
}

void				moveLeft(void) {
	_mLeftPressed = true;
}

void				stopLeft(void) {
	_mLeftPressed = false;
}

// Overloaded Public Actor Methods --
void				Player::tick(void) {

}
