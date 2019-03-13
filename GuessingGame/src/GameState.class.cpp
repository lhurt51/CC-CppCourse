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
#include "MenuHandler.class.hpp"
#include "GameState.class.hpp"
#include "GameEngine.class.hpp"

// Initializer for window dimensions Constructor
GameState::GameState(Vector2D<uint_fast32_t> const winDem) : _winDem(winDem), _curState(STARTING), _menuHandler(nullptr) {
	return;
}

// Copy constructor
GameState::GameState(GameState const &src) {
	*this = src;
	return;
}

// Deconstructor
GameState::~GameState(void) {
	_deleteMenuHandler();
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

// Set the current state and return the previous state
State							GameState::setCurState(State curState) {
	static State lastState = STARTING;

	if (this->_curState == curState) return lastState;
	else if (_curState != LOADING && _curState != ERROR) lastState = this->_curState;
	this->_curState = curState;
	return lastState;
}

// Handle the input for all the actors that require input
void							GameState::handleInput(int input) {
	if (input == 'q') setCurState(EXITING);
	if (_menuHandler) {
		if (_menuHandler->getIsHorizontal()) {
			if (input == 'a') _menuHandler->decreaseIndexItem();
			if (input == 'd') _menuHandler->increaseIndexItem();
		} else {
			if (input == 'w') _menuHandler->decreaseIndexItem();
			if (input == 's') _menuHandler->increaseIndexItem();
		}
		if (input == 'e') _menuHandler->doExecute();
	}
}

// Run the state based on current state
bool							GameState::runState(void) {
	switch (_curState) {
		case LOADING:
			_handleLoadingState();
			break;
		case STARTING:
			_handleStartingState();
			break;
		case INPUTING:
			_handleInputingState();
			break;
		case PLAYING:
			_handlePlayingState();
			break;
		case TESTING:
			_handleTestingState();
			break;
		case GAMEOVER:
			_handleGameOverState();
			break;
		case ERROR:
			_handleErrorState();
			break;
		case EXITING:
			_handleExitingState();
			return false;
		default:
			break;
	}
	_draw();
	return true;
}

bool							GameState::_checkStateChange(void) {
	static State lastState = setCurState(_curState);

	if (lastState != setCurState(_curState)) {
		lastState = setCurState(_curState);
		return true;
	}
	return false;
}

// Redraw the screen with all actors and messages
void                        	GameState::_draw(void) {
	static Vector2D<uint_fast32_t> lastDem;
	static float fps = GameEngine::calculateFPS();

	if (Actor::anyActorNeedsUpdate() || _winDem != lastDem || fps != GameEngine::calculateFPS()) {
		clear();
		if (_curState == ERROR)
			GameEngine::printMiddle(_winDem, WIN_2_SMALL_MSG);
		else {
			char	buffer[128];

			fps = GameEngine::calculateFPS();
			snprintf(buffer, sizeof(buffer), GAME_FPS, fps);
			GameEngine::printPos(Vector2D<uint_fast32_t>(10, 1), buffer);
			GameEngine::printBorder();
		}
		Actor::printAllActors();
		Actor::resetAllActorsNeedsUpdate();
	}
}

// Handle the loading state update
void							GameState::_handleLoadingState(void) {
	if(GameEngine::isWindowToSmall(_winDem)) {
		Actor::setAllActorsCanDraw(false);
		setCurState(ERROR);
	} else {
		Actor::setAllActorsCanDraw(true);
		setCurState(setCurState(LOADING));
	}
}

// Handle the starting state update
void							GameState::_handleStartingState(void) {
	static bool first = true;

	if ((first && _menuHandler) || _checkStateChange()) {
		_deleteMenuHandler();
		first = false;
	}
	if (!_menuHandler)
		_menuHandler = new MenuHandler(*this, MAIN_MENU_TITLE, { MAIN_MENU_START_B, MAIN_MENU_TEST_B, MAIN_MENU_EXIT_B }, false);
	Actor::tickAllActors();
}

// Handle input state update
void							GameState::_handleInputingState(void) {

}

// Handle playing state update
void							GameState::_handlePlayingState(void) {
	static bool first = true;

	if ((first && _menuHandler) || _checkStateChange()) {
		_deleteMenuHandler();
		first = false;
	}
	if (!_menuHandler)
		_menuHandler = new MenuHandler(*this, IN_GAME_MENU_TITLE, { IN_GAME_MENU_INC_B, IN_GAME_MENU_DEC_B }, true);
	Actor::tickAllActors();
}

void							GameState::_handleTestingState(void) {
	static bool first = true;

	if ((first && _menuHandler) || _checkStateChange()) {
		_deleteMenuHandler();
		first = false;
	}
	if (!_menuHandler)
		_menuHandler = new MenuHandler(*this, TESTING_MENU_TITLE, { TESTING_MENU_EXIT_B }, true);
	Actor::tickAllActors();
}

// Handle game over state update
void 							GameState::_handleGameOverState(void) {
	Actor::tickAllActors();
}

// Handle error state update
void 							GameState::_handleErrorState(void) {
	return;
}

// Handle the exiting state update
void							GameState::_handleExitingState(void) {
	_deleteMenuHandler();
}

// Delete the menu handler as long as its allocated
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
