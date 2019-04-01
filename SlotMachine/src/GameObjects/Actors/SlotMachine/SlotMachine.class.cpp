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
#include "Timers/Timer.class.hpp"
#include "Timers/AsynFuncTimer.class.hpp"
#include "Numbers.class.hpp"
#include "SlotMachine.class.hpp"
#include "Handlers/GameStateHandler.class.hpp"

// Initializing the player sprite
const std::string playerSprite = "Slot Machine";

// Default constructor to initialize all attributes
SlotMachine::SlotMachine(void) : Actor(GameStateHandler::getWinDim() / (unsigned)2, playerSprite), _gameOverDsp(nullptr), _interval(20.0), _timer(nullptr), _bet(100), _winnings(0) {
	_bet = 5;
	setTimer();
	setNumbers();
	return;
}

// Copy constructor
SlotMachine::SlotMachine(SlotMachine const &src) : Actor(src) {
	*this = src;
	return;
}

// Deconstructor
SlotMachine::~SlotMachine(void) {
	deleteTimer();
	deleteNumbers();
	if (_gameOverDsp) delete _gameOverDsp;
	return;
}

// Overload equals operators for copy constructor
SlotMachine&			SlotMachine::operator=(SlotMachine const &rhs) {
	if (this != &rhs) {
		this->_timer = rhs.getTimer();
		this->_numbers = rhs.getNumbers();
	}
	return *this;
}

// Getters --
Timer*						SlotMachine::getTimer(void) const {
	return this->_timer;
}

std::vector<Numbers*>		SlotMachine::getNumbers(void) const {
	return this->_numbers;
}

// Setters --
void						SlotMachine::setTimer(void) {
	if (!_timer) _timer = new Timer();
}

void						SlotMachine::setNumbers(void) {
	_numbers.clear();
	for (unsigned i = 0; i < 3; i++) {
		Vector2D<uint_fast32_t> tmp = ((i == 0) ? Vector2D<uint_fast32_t>(10, 5) : Vector2D<uint_fast32_t>(0, 5));
		_numbers.push_back(new Numbers(GameStateHandler::getWinDim() / (unsigned)2 - tmp + ((i == 2) ?  Vector2D<uint_fast32_t>(10, 0) : Vector2D<uint_fast32_t>(0, 0))));
	}
}

void						SlotMachine::startRoll(void) {
	static unsigned index = 0;

	if (index >= 3) {
		if (_gameOverDsp) return;
		std::string str = "Roll Over\nYou won ";
		_winnings += _bet * 5;
		str += std::to_string(_winnings) + "$";
		_gameOverDsp = new GameObject(_pos + Vector2D<uint_fast32_t>(0, 2), str);
		return;
	} else if (_timer->elapsed() >= 0.1 && _timer->elapsed() <= _interval - 1) {
		if (_numbers[index]) _numbers[index]->incInterval();
	} else if (_timer->elapsed() >= _interval - 1 && _timer->elapsed() <= _interval) {
		if (_numbers[index]) _numbers[index]->stopRolling();
	} else if (_timer->elapsed() > _interval) {
		_timer->reset();
		index++;
	}

}

// Overloaded Public Actor Method
void						SlotMachine::tick(void) {
	if (!_timer || _numbers.size() < 1) return;
	startRoll();
}

void						SlotMachine::deleteTimer(void) {
	if (_timer) {
		delete _timer;
		_timer = nullptr;
	}
}

void						SlotMachine::deleteNumbers(void) {
	for (std::vector<Numbers*>::iterator pObj = _numbers.begin(); pObj != _numbers.end(); ++pObj)
		delete *pObj;
	_numbers.clear();
}
