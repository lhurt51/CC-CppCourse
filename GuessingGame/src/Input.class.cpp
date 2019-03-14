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
#include "Input.class.hpp"

// Default constructor to initialize all attributes
Input::Input(GameState &gameState, Vector2D<uint_fast32_t> pos) : Actor(pos, INPUT_START_MSG), _gameState(gameState), _bIsTyping(true) {
	addInputToString(-2);
	return;
}

// Copy constructor
Input::Input(Input const &src) : Actor(src), _gameState(src.getGameState()) {
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
		this->_gameState = rhs.getGameState();
	}
	return *this;
}

// Getters --
GameState			&Input::getGameState(void) const {
	return this->_gameState;
}

bool				Input::getIsTyping(void) const {
	return this->_bIsTyping;
}

// Setters --
void				Input::setIsTyping(void) {
	if (!_bIsTyping) return;
	if (_is_digits(_sprite)) _bIsTyping = false;
	else if (_is_alphas(_sprite)) _bIsTyping = false;
	else addInputToString(-1);
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
	} else setSprite(this->_sprite + (char)input);
}

void				Input::finnishInput(void) {
	if (!_bIsTyping)
		_gameState.setCurState((_gameState.bIsPlaying) ? PLAYING : TESTING);
}

// Overloaded Public Actor Method
void				Input::tick(void) {
	setPos(Vector2D<uint_fast32_t>(HALF_OF_VAL(_gameState.getWinDem().x), HALF_OF_VAL(_gameState.getWinDem().y)));
}

bool 				Input::_is_digits(const std::string &str)
{
    return std::all_of(str.begin(), str.end(), ::isdigit); // C++11
}

bool 				Input::_is_alphas(const std::string &str)
{
    return std::all_of(str.begin(), str.end(), ::isalpha); // C++11
}
