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

#include <vector>
#include <macros/main_game_macros.hpp>
#include "Vector2D.class.hpp"
#include "Timers/Timer.class.hpp"
#include "RandomNumGenerator/RandNumGen.class.hpp"
#include "Numbers.class.hpp"

// Initializing ascii numbers
const std::vector< std::string > asciiNumbers =
{
{" __  \n/_ | \n | | \n | | \n | | \n |_| "}, // 1
{" ___   \n|__ \\  \n   ) | \n  / /  \n / /_  \n|____| "}, // 2
{" ____  \n|___ \\\n ___) |\n|___ < \n ___) |\n|____/ "}, // 3
{" _  _  \n| || | \n| || |_\n|__ _| \n  | |  \n  |_|  "}, // 4
{" _____ \n| ____|\n| |__  \n|___ \\\n ___) |\n|____/ "}, // 5
{"   __   \n  / /   \n / /_   \n| '_ \\  \n| (_) | \n \\___/  "}, // 6
{" ______ \n|____  |\n    / / \n   / /  \n  / /   \n /_/    \n"}, // 7
{" _____ \n/  _  \\\n| (_) |\n > _ < \n| (_) |\n\\_____/"}, // 8
{"___ \n / _ \\  \n| (_) | \n\\__, | \n   / /  \n  /_/   "}, // 9
{" _____ \n/  _  \\\n| | | |\n| | | |\n| |_| |\n\\_____/"} // 0
};

// Default constructor to initialize all attributes
Numbers::Numbers(Vector2D<uint_fast32_t> pos) : Actor(pos, asciiNumbers[0]), _bRolling(true), _interval(0.01), _timer(nullptr), _randNumGen(nullptr) {
	if (!_randNumGen) _randNumGen = new RandNumGen(0, asciiNumbers.size());
	if (!_timer) _timer = new Timer();
	changeSprite();
	return;
}

// Copy constructor
Numbers::Numbers(Numbers const &src) : Actor(src) {
	*this = src;
	return;
}

// Deconstructor
Numbers::~Numbers(void) {
	if (_randNumGen) {
		delete _randNumGen;
		_randNumGen = nullptr;
	}
	if (_timer) {
		delete _timer;
		_timer = nullptr;
	}
	return;
}

// Overload equals operators for copy constructor
Numbers&				Numbers::operator=(Numbers const &rhs) {
	if (this != &rhs) {
		this->_curNum = rhs.getCurNum();
		this->_timer = rhs.getTimer();
	}
	return *this;
}

// Getters --
unsigned				Numbers::getCurNum(void) const {
	return this->_curNum;
}

Timer*					Numbers::getTimer(void) const {
	return this->_timer;
}

// Setters --
void					Numbers::stopRolling(void) {
	this->_bRolling = false;
}

void					Numbers::incInterval(void) {
	this->_interval *= 1.000001;
}

// Helper Methods --
void					Numbers::changeSprite(void) {
	if (_randNumGen) {
		_curNum = _randNumGen->getNextRand();
		setSprite(asciiNumbers[_curNum]);
	}
}

// Overloaded Public Actor Method
void					Numbers::tick(void) {
	if (_bRolling && _timer->elapsed() > _interval) {
		changeSprite();
		_timer->reset();
	}
}
