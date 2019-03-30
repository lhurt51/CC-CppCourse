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

#include <unistd.h>
#include <macros/game_state_macros.hpp>
#include "Vector2D.class.hpp"
#include "GameState/StartingState.class.hpp"
#include "GameState/PlayingState.class.hpp"
#include "GameStateHandler.class.hpp"
#include "GameEngine.class.hpp"

Vector2D<uint_fast32_t> 		GameStateHandler::_winDem(MIN_WIN_SIZE);
State							GameStateHandler::_curState = STARTING;
GameState*						GameStateHandler::_gameState = nullptr;

// Game State Getters --
Vector2D<uint_fast32_t>			GameStateHandler::getWinDim(void) {
	return _winDem;
}

State							GameStateHandler::getCurState(void) {
	return _curState;
}

GameState*						GameStateHandler::getGameState(void) {
	return _gameState;
}

// Game State Setters --
void							GameStateHandler::setWinDim(Vector2D<uint_fast32_t> winDem) {
	if (_winDem == winDem) return;
	_winDem = winDem;
	if (_gameState) _gameState->handleResize();
	setCurState(LOADING);
}

// Set the current state and return the previous state
State							GameStateHandler::setCurState(State curState) {
	static State lastState = STARTING;

	if (_curState == curState)
		return lastState;
	else if (_curState != LOADING && _curState != ERROR)
		lastState = _curState;
	_curState = curState;
	return lastState;
}

void							GameStateHandler::setGameState(GameState *gameState) {
	if (_gameState == gameState) return;
	_gameState = gameState;
}

// Handle the input for all the actors that require input
void							GameStateHandler::handleInput(int input) {
	if (input == '`') setCurState(EXITING);
	if (_gameState) _gameState->handleInput(input);
}

// Run the state based on current state
bool							GameStateHandler::runState(void) {
	bool stateChange = _checkStateChange();

	switch (_curState) {
		case LOADING:
			_handleLoadingState();
			break;
		case EXITING:
			_deleteGameState();
			return false;
		default:
			if (_gameState) _gameState->handleTick();
			break;
	}
	_draw(stateChange);
	return true;
}

void							GameStateHandler::_chooseGameState(void) {
	_deleteGameState();
	switch(_curState) {
		case STARTING:
			if (!_gameState) _gameState = new StartingState();
			break;
		case PLAYING:
			if (!_gameState) _gameState = new PlayingState();
			break;
		default:
			_gameState = nullptr;
			break;
	}
}

bool							GameStateHandler::_checkStateChange(void) {
	static State lastState;

	if (lastState != _curState) {
		lastState = _curState;
		if (_curState == STARTING || _curState == PLAYING)
			_chooseGameState();
		return true;
	}
	return false;
}

bool							GameStateHandler::_checkWinDimChange(void) {
	static Vector2D<uint_fast32_t> lastDem;

	if (lastDem != _winDem) {
		lastDem = _winDem;
		return true;
	}
	return false;
}

// Redraw the screen with all actors and messages
void                        	GameStateHandler::_draw(bool stateChange) {
	static float fps = GameEngine::calculateFPS();

	if (_checkWinDimChange() || fps != GameEngine::calculateFPS() || (_gameState && _gameState->checkForActorUpdate()) || stateChange) {
		GameEngine::clearScreen();
		if (_curState == ERROR)
			GameEngine::printMiddle(WIN_2_SMALL_MSG);
		else {
			fps = GameEngine::calculateFPS();
			std::string tmp = GAME_FPS + std::to_string(fps);
			GameEngine::printPos(Vector2D<uint_fast32_t>(HALF_OF_VAL(tmp.length()) + 2, 1), tmp);
			if (_gameState) _gameState->printAllGameObjects();
			GameEngine::printBorder();
		}
		GameEngine::refreshScreen();
	}
}

// Handle the loading state update
void							GameStateHandler::_handleLoadingState(void) {
	if(GameEngine::isWindowToSmall()) {
		if (_gameState)
			_gameState->hideAllGameObjects();
		setCurState(ERROR);
	} else {
		if (_gameState)
			_gameState->showAllGameObjects();
		setCurState(setCurState(LOADING));
	}
}

void							GameStateHandler::_deleteGameState(void) {
	if (_gameState) {
		delete _gameState;
		_gameState = nullptr;
	}
}

// Out stream overload for testing
std::ostream					&operator<<(std::ostream &o, GameStateHandler const &i) {
	return o << "Game State Info:" << std::endl <<
	"window dimensions: " << i.getWinDim() << std::endl <<
	"state: " << i.getCurState() << std::endl << i.getGameState();
}
