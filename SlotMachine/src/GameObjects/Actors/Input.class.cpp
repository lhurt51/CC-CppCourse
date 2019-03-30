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

#include <macros/input_macros.hpp>
#include "Vector2D.class.hpp"
#include "Input.class.hpp"
#include "Handlers/GameStateHandler.class.hpp"

// Default constructor to initialize all attributes
Input::Input(Vector2D<uint_fast32_t> pos) : Actor(pos, INPUT_START_MSG), _bIsTyping(true) {
	addInputToString(-2);
	return;
}

// Copy constructor
Input::Input(Input const &src) : Actor(src) {
	*this = src;
	return;
}

// Deconstructor
Input::~Input(void) {
	return;
}

// Overload equals operators for copy constructor
Input&				Input::operator=(Input const &rhs) {
	if (this != &rhs) {
		this->_bIsTyping = rhs.getIsTyping();
		this->_bIsChar = rhs.getIsChar();
	}
	return *this;
}

// Getters --
bool				Input::getIsTyping(void) const {
	return this->_bIsTyping;
}

bool				Input::getIsChar(void) const {
	return this->_bIsChar;
}

// Setters --
void				Input::setIsTyping(void) {
	if (!_bIsTyping) return;
	if (_is_digits(_sprite)) {
		_bIsTyping = false;
		_bIsChar = false;
	} else if (_is_alphas(_sprite)) {
		_bIsTyping = false;
		_bIsChar = true;
	} else addInputToString(-1);
}

void				Input::addInputToString(int input) {
	static bool first = true;

	if (!_bIsTyping) return;
	if (input < 0) {
		first = true;
		if (input == -1)
			setSprite(INPUT_EXIT_MSG);
	} else if (first) {
		std::string tmp = "";
		setSprite(tmp + (char)input);
		first = false;
	} else {
		setSprite(this->_sprite + (char)input);
		if (getSprite().length() > 3) setIsTyping();
	}
}

void				Input::finnishInput(void) {
	if (!_bIsTyping) return;
		GameStateHandler::setCurState(PLAYING);
}

// Overloaded Public Actor Method
void				Input::tick(void) {
	setPos(Vector2D<uint_fast32_t>(HALF_OF_VAL(GameStateHandler::getWinDim().x), HALF_OF_VAL(GameStateHandler::getWinDim().y)));
}

bool 				Input::_is_digits(const std::string &str)
{
    return std::all_of(str.begin(), str.end(), ::isdigit); // C++11
}

bool 				Input::_is_alphas(const std::string &str)
{
    return std::all_of(str.begin(), str.end(), ::isalpha); // C++11
}
