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
#include "MenuHandler.class.hpp"
#include "Input.class.hpp"
#include "GameState.class.hpp"
#include "GameStateHandler.class.hpp"
#include "GameEngine.class.hpp"

// Initializer for window dimensions Constructor
GameStateHandler::GameStateHandler(Vector2D<uint_fast32_t> const winDem) : _winDem(winDem), _curState(STARTING) {
	return;
}

// Copy constructor
GameStateHandler::GameStateHandler(GameStateHandler const &src) {
	*this = src;
	return;
}

// Deconstructor
GameStateHandler::~GameStateHandler(void) {
	return;
}

// Equal sign overload for the copy constructor
GameStateHandler						&GameStateHandler::operator=(GameStateHandler const &rhs) {
	if (this != &rhs) {
		this->_winDem = rhs.getWinDem();
		this->_curState = rhs.getCurState();
	}
	return *this;
}

// Game State Getters --
Vector2D<uint_fast32_t> const	GameStateHandler::getWinDem(void) const {
	return this->_winDem;
}

State							GameStateHandler::getCurState(void) const {
	return this->_curState;
}

GameState*						GameStateHandler::getGameState(void) const {
	return this->_gameState;
}

// Game State Setters --
void							GameStateHandler::setWinDem(Vector2D<uint_fast32_t> winDem) {
	if (this->_winDem == winDem)
		return;
	this->_winDem = winDem;
	setCurState(LOADING);
}

// Set the current state and return the previous state
State							GameStateHandler::setCurState(State curState) {
	static State lastState = STARTING;

	if (this->_curState == curState)
		return lastState;
	else if (_curState != LOADING && _curState != ERROR)
		lastState = this->_curState;
	this->_curState = curState;
	return lastState;
}

void							GameStateHandler::setGameState(GameState *gameState) {
	if (this->_gameState == gameState) return;
	this->_gameState = gameState;
}

// Handle the input for all the actors that require input
void							GameStateHandler::handleInput(int input) {
	if (input == '`') setCurState(EXITING);
}

// Run the state based on current state
bool							GameStateHandler::runState(void) {
	switch (_curState) {
		case LOADING:
			_handleLoadingState();
			break;
		case STARTING:
			_handleStartingState();
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
	Actor::tickAllActors();
	_draw();
	return true;
}

bool							GameStateHandler::_checkStateChange(void) {
	static State lastState = setCurState(_curState);

	if (lastState != setCurState(_curState)) {
		lastState = setCurState(_curState);
		return true;
	}
	return false;
}

// Redraw the screen with all actors and messages
void                        	GameStateHandler::_draw(void) {
	static Vector2D<uint_fast32_t> lastDem = _winDem;
	static float fps = GameEngine::calculateFPS();

	if (Actor::anyActorNeedsUpdate() || lastDem != _winDem || _checkStateChange() || fps != GameEngine::calculateFPS()) {
		GameEngine::clearScreen();
		if (_curState == ERROR)
			GameEngine::printMiddle(WIN_2_SMALL_MSG);
		else {
			fps = GameEngine::calculateFPS();
			std::string tmp = GAME_FPS + std::to_string(fps);
			GameEngine::printPos(Vector2D<uint_fast32_t>(HALF_OF_VAL(tmp.length()) + 2, 1), tmp);
			GameEngine::printBorder();
		}
		Actor::printAllActors();
		Actor::resetAllActorsNeedsUpdate();
		lastDem = _winDem;
	}
}

// Handle the loading state update
void							GameStateHandler::_handleLoadingState(void) {
	if(GameEngine::isWindowToSmall()) {
		Actor::setAllActorsCanDraw(false);
		setCurState(ERROR);
	} else {
		Actor::setAllActorsCanDraw(true);
		setCurState(setCurState(LOADING));
	}
}

// Handle the starting state update
void							GameStateHandler::_handleStartingState(void) {
	return;
}

// Handle playing state update
void							GameStateHandler::_handlePlayingState(void) {
	return;
}

void							GameStateHandler::_handleTestingState(void) {
	return;
}

// Handle game over state update
void 							GameStateHandler::_handleGameOverState(void) {
	return;
}

// Handle error state update
void 							GameStateHandler::_handleErrorState(void) {
	return;
}

// Handle the exiting state update
void							GameStateHandler::_handleExitingState(void) {
	return;
}

// Out stream overload for testing
std::ostream					&operator<<(std::ostream &o, GameStateHandler const &i) {
	return o << "Game State Info:" << std::endl <<
	"window demensions: " << i.getWinDem() << std::endl <<
	"state: " << i.getCurState() << std::endl;
}
