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

#include <ncurses.h>
#include <typedefs.hpp>
#include "Vector2D.class.hpp"
#include "Player.class.hpp"
#include "MenuHandler.class.hpp"
#include "GameState.class.hpp"
#include "GameEngine.class.hpp"

// Initializer for window dimensions Constructor
GameState::GameState(Vector2D<uint_fast32_t> const winDem) : _winDem(winDem), _curState(LOADING), _menuHandler(nullptr) {
	_player = new Player();
	return;
}

// Copy constructor
GameState::GameState(GameState const &src) {
	*this = src;
	return;
}

// Deconstructor
GameState::~GameState(void) {
	_deletePlayer();
	return;
}

// Equal sign overload for the copy constructor
GameState						&GameState::operator=(GameState const &rhs) {
	if (this != &rhs) {
		this->_winDem = rhs.getWinDem();
		this->_curState = rhs.getCurState();
	}
	return *this;
}

// Game State Getters --
Vector2D<uint_fast32_t> const	GameState::getWinDem(void) const {
	return this->_winDem;
}

State							GameState::getCurState(void) const {
	return this->_curState;
}

// Game State Setters --
void							GameState::setWinDem(Vector2D<uint_fast32_t> const winDem) {
	if (this->_winDem == winDem) return;
	this->_winDem = winDem;
	setCurState(LOADING);
}

State							GameState::setCurState(State curState) {
	static State lastState = STARTING;

	if (this->_curState == curState) return lastState;
	else if (_curState != LOADING && _curState != ERROR) lastState = this->_curState;
	this->_curState = curState;
	return lastState;
}

void							GameState::handleInput(int input) {
	if (input == 'q') setCurState(EXITING);
	else if (_player) {
		if (input == 'a') _player->moveLeft();
		else _player->stopLeft();
		if (input == 'd') _player->moveRight();
		else _player->stopRight();
	}
}

bool							GameState::runState(void) {
	if (_player && _player->getPos().x >= _winDem.x) _deletePlayer();
	if (!_menuHandler) {
		std::vector<std::string> myItems;
		myItems.push_back("item1");
		myItems.push_back("item2");
		myItems.push_back("item3");
		myItems.push_back("item4");

		_menuHandler = new MenuHandler(*this, "Menu", myItems);
	}
	switch (_curState) {
		case LOADING:
			_handleLoadingState();
			break;
		case ERROR:
			_handleErrorState();
			break;
		case EXITING:
			_handleExitingState();
			return false;
		default:
			Actor::tickAllActors();
			break;
	}
	_draw();
	return true;
}

void                        	GameState::_draw(void) {
	static Vector2D<uint_fast32_t> lastDem;
	static float fps = GameEngine::calculateFPS();
	static State lastState;

	lastState = setCurState(_curState);
	if (Actor::anyActorNeedsUpdate() || _winDem != lastDem || fps != GameEngine::calculateFPS() || lastState != _curState) {
		clear();
		if (_curState == ERROR)
			GameEngine::printMiddle(_winDem, WIN_2_SMALL_MSG);
		else {
			char	buffer[128];

			fps = GameEngine::calculateFPS();
			snprintf(buffer, sizeof(buffer), GAME_FPS, fps);
			GameEngine::printPos(Vector2D<uint_fast32_t>(10, 1), buffer);
			if (_menuHandler) _menuHandler->updateMenus();
			GameEngine::printBorder();
		}
		Actor::printAllActors();
		Actor::resetAllActorsNeedsUpdate();
	}
	lastDem = _winDem;
}

void							GameState::_handleLoadingState(void) {
	if(GameEngine::isWindowToSmall(_winDem)) {
		Actor::setAllActorsCanDraw(false);
		setCurState(ERROR);
	} else {
		Actor::setAllActorsCanDraw(true);
		setCurState(setCurState(LOADING));
	}
}

void							GameState::_handleStartingState(void) {

}

void							GameState::_handlePlayingState(void) {

}

void 							GameState::_handleGameOverState(void) {

}

void 							GameState::_handleErrorState(void) {

}

void							GameState::_handleExitingState(void) {
	_deletePlayer();
	_deleteMenuHandler();
}

void							GameState::_deletePlayer(void) {
	if (_player) {
		delete _player;
		_player = nullptr;
	}
}

void							GameState::_deleteMenuHandler(void) {
	if (_menuHandler) {
		delete _menuHandler;
		_menuHandler = nullptr;
	}
}

// Out stream overload for testing
std::ostream					&operator<<(std::ostream &o, GameState const &i) {
	return o << "Game State Info:" << std::endl <<
	"window demensions: " << i.getWinDem() << std::endl <<
	"state: " << i.getCurState() << std::endl;
}
