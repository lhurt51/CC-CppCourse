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

#include "AsynFuncTimer.class.hpp"

AsynFuncTimer::AsynFuncTimer(std::function<void(void)> func, const long &interval) : _func(func), _interval(interval) {
	return;
}

AsynFuncTimer::~AsynFuncTimer(void) {
	stop();
	return;
}

bool						AsynFuncTimer::isRunning(void) const {
	return this->_running;
}

long						AsynFuncTimer::getInterval(void) const {
	return this->_interval;
}

AsynFuncTimer*				AsynFuncTimer::setFunc(std::function<void(void)> func) {
	this->_func = func;
	return this;
}

AsynFuncTimer*				AsynFuncTimer::setInterval(const long &interval) {
	this->_interval = interval;
	return this;
}

void						AsynFuncTimer::start(void) {
	_running = true;
	_thread = std::thread([&]() {
		while (_running) {
			auto delta = std::chrono::steady_clock::now() + std::chrono::milliseconds(_interval);
			_func();
			std::this_thread::sleep_until(delta);
		}
	});
	_thread.detach();
}

void						AsynFuncTimer::stop(void) {
	_running = false;
	_thread.~thread();
}

void						AsynFuncTimer::reset(void) {
	stop();
	start();
}
