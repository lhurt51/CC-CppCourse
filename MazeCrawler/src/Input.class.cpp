/*******************************************************************************\
* Programmer Name:																*
* Liam Hurt																		*
*																				*
* Date:																			*
* 3/16/2019																		*
*																				*
* Assignment Requirement:														*
* 7.33 (Maze Traversal) The grid of hashes (#) and dots (.) in Fig. 7.29 is a	*
* two-dimensional builtin array representation of a maze. In the				*
* two-dimensional built-in array, the hashes represent the walls of the maze	*
* and the dots represent squares in the possible paths through the maze. Moves	*
* can be made only to a location in the built-in array that contains a dot.		*
* There is a simple algorithm for walking through a maze that guarantees to		*
* find the exit (assuming that there is an exit). If there is not an exit,		*
* you’ll arrive at the starting location again. Place your right hand on		*
* the wall to your right and begin walking forward. Never remove your hand		*
* from the wall. If the maze turns to the right, you follow the wall to the		*
* right. As long as you do not remove your hand from the wall, eventually		*
* you’ll arrive at the exit of the maze. There may be a shorter path than the	*
* one you’ve taken, but you are guaranteed to get out of the maze if you		*
* follow the algorithm.															*
*																				*
*  # # # # # # # # # # # #														*
*  # . . . # . . . . . . #														*
*  . . # . # . # # # # . #														*
*  # # # . # . . . . # . #														*
*  # . . . . # # # . # . .														*
*  # # # # . # . # . # . #														*
*  # . . # . # . # . # . #														*
*  # # . # . # . # . # . #														*
*  # . . . . . . . . # . #														*
*  # # # # # # . # # # . #														*
*  # . . . . . . # . . . #														*
*  # # # # # # # # # # # #														*
*																				*
* Write recursive function mazeTraverse to walk through the maze. The function	*
* should receive arguments that include a 12-by-12 built-in array of chars		*
* representing the maze and the starting location of the maze. As mazeTraverse	*
* attempts to locate the exit from the maze, it should place the character X	*
* in each square in the path. The function should display the maze after each	*
* move, so the user can watch as the maze is solved.							*
*																				*
\*******************************************************************************/

#include <macros/input_macros.hpp>
#include "Vector2D.class.hpp"
#include "Input.class.hpp"
#include "GameStateHandler.class.hpp"

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
