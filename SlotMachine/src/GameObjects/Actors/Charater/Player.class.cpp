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

#include <macros/main_game_macros.hpp>
#include "Vector2D.class.hpp"
#include "Player.class.hpp"

// Initializing the player sprite
const std::string playerSprite = "Player";

// Default constructor to initialize all attributes
Player::Player(void) : Actor(Vector2D<uint_fast32_t>(DEFAULT_SPAWN), playerSprite), _bIsTyping(false), _mRightPressed(false), _mLeftPressed(false) {
	return;
}

// Copy constructor
Player::Player(Player const &src) : Actor(src) {
	*this = src;
	return;
}

// Deconstructor
Player::~Player(void) {
	return;
}

// Overload equals operators for copy constructor
Player&				Player::operator=(Player const &rhs) {
	if (this != &rhs) {
		this->_bIsTyping = rhs.getIsTyping();
		this->_mRightPressed = rhs.getPressingRight();
		this->_mLeftPressed = rhs.getPressingLeft();
	}
	return *this;
}

// Getters --
bool				Player::getIsTyping(void) const {
	return this->_bIsTyping;
}

bool				Player::getPressingRight(void) const {
	return this->_mRightPressed;
}

bool				Player::getPressingLeft(void) const {
	return this->_mLeftPressed;
}

// Setters --
void				Player::startTyping(void) {
	this->_bIsTyping = true;
}

void				Player::stopTyping(void) {
	this->_bIsTyping = false;
}

void				Player::moveRight(void) {
	this->_mRightPressed = true;
}

void				Player::stopRight(void) {
	this->_mRightPressed = false;
}

void				Player::moveLeft(void) {
	this->_mLeftPressed = true;
}

void				Player::stopLeft(void) {
	this->_mLeftPressed = false;
}

// Move the actor based on a Vector2D
bool				Player::move(Vector2D<uint_fast32_t> dst) {
	if (dst == Vector2D<uint_fast32_t>()) return false;
	_pos += dst;
	_bNeedsUpdate = true;
	return true;
}

// Overloaded Public Actor Method
void				Player::tick(void) {
	if (_mRightPressed) move(Vector2D<uint_fast32_t>(1, 0));
	if (_mLeftPressed) move(Vector2D<uint_fast32_t>(-1, 0));
}
