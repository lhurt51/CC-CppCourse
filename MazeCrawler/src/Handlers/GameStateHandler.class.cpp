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
	static bool first = true;
	static State lastState = STARTING;

	if (_curState == curState)
		return lastState;
	else if (_curState != LOADING && _curState != ERROR) {
		lastState = _curState;
	}
	_curState = curState;
	if ((_curState != LOADING && _curState != ERROR && (lastState != _curState || first))) {
		_chooseGameState();
		first = false;
	}
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
	_draw();
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
			break;
	}
}

bool							GameStateHandler::_checkStateChange(void) {
	static State lastState;

	if (lastState != setCurState(_curState)) {
		lastState = setCurState(_curState);
		return true;
	}
	return false;
}

bool							GameStateHandler::_checkWinDimChange(void) {
	static Vector2D<uint_fast32_t> lastDem = _winDem;

	if (lastDem != _winDem) {
		lastDem = _winDem;
		return true;
	}
	return false;
}

// Redraw the screen with all actors and messages
void                        	GameStateHandler::_draw(void) {
	static float fps = GameEngine::calculateFPS();

	if (_checkStateChange() || _checkWinDimChange() || fps != GameEngine::calculateFPS() || (_gameState && _gameState->checkForActorUpdate())) {
		GameEngine::clearScreen();
		if (_curState == ERROR)
			GameEngine::printMiddle(WIN_2_SMALL_MSG);
		else {
			fps = GameEngine::calculateFPS();
			std::string tmp = GAME_FPS + std::to_string(fps);
			GameEngine::printPos(Vector2D<uint_fast32_t>(HALF_OF_VAL(tmp.length()) + 2, 1), tmp);
			GameEngine::printBorder();
			if (_gameState) _gameState->printAllGameObjects();
		}
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
