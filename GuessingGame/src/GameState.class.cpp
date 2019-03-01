/******************************************************************************
* Programmer Name:
* Liam Hurt
*
* Date:
* 2/6/2019
*
* Assignment Requirement:
* Develop and test a connect - 4 like game except:
*
* Only need to connect 3
* There will be 3 players
* Only need to connect vertical and horizontal
* Use a board of 5 by 6 with header for the column number
* Use ASCII graphics
*
******************************************************************************/

#include <time.h>
#include <typedefs.hpp>
#include "Game.class.hpp"
#include "GameState.class.hpp"

// Initializer for windem Constructor
GameState::GameState(Vector2D<uint_fast32_t> winDem) : _winDem(winDem), _curState(LOADING) {
	//_initAllActors();
	return;
}

// Copy constructor
GameState::GameState(GameState const &src) {
	*this = src;
	return;
}

// Deconstructor
GameState::~GameState(void) {
	//_deleteAllActors();
	return;
}

// Equal sign overload for the copy constructor
GameState				&GameState::operator=(GameState const &rhs) {
	if (this != &rhs) {
		this->_winDem = rhs.getWinDem();
		this->_curState = rhs.getCurState();
	}
	return *this;
}

// Game State Getters --
Vector2D<uint_fast32_t>	GameState::getWinDem(void) const {
	return this->_winDem;
}

State					GameState::getCurState(void) const {
	return this->_curState;
}
// Game State Getters --

// Game State Setters --
void					GameState::setWinDem(Vector2D<uint_fast32_t> winDem) {
	if (this->_winDem == winDem) return;
	this->_winDem = winDem;
	setCurState(LOADING);
}

void					GameState::setCurState(State curState) {
	if (this->_curState == curState) return;
	this->_curState = curState;
}
// Game State Setters --

// Check for exit request a request break from program
/*
bool					GameState::bShouldExit(void) {
	for (unsigned int i = 0; i < _players.size(); i++) {
		if (_players[i].getExitReq())
			return true;
	}
	return false;
}
*/

// Run the main game loop base on the current state
void					GameState::runMainLoop(void) {
	switch (_curState) {
		case LOADING:
			_curState = PLAYING;
			runWinUpdate(Game::isWindowToSmall());
		case PLAYING:
			//_tickAllActors();
			break;
		case GAMEOVER:
			_handleGameOver();
			break;
		default:
			break;
	}
}

// Run a window update checking for a too small screen otherwise based off of current state
void					GameState::runWinUpdate(bool bIsToSmall) {
	char title[] = "Connect 3";
	char error[] = "Window too small";

	clear();
	if (bIsToSmall) {
		//_setAllActorsCanDraw(false);
		mvprintw(HALF_OF_VAL(_winDem.y), HALF_OF_VAL(_winDem.x) - HALF_OF_VAL(strlen(error)), error);
	} else {
		switch(_curState) {
			case LOADING:
				_curState = PLAYING;
			case PLAYING:
				_mainWindowRedraw();
				break;
			case GAMEOVER:
				_gameOverWindowRedraw();
				break;
			default:
				break;
		}
		mvprintw(3, HALF_OF_VAL(_winDem.x) - HALF_OF_VAL(strlen(title)), title);
	}
	wborder(Game::getWindow(), '|', '|', '-', '-', 'o', 'o', 'o', 'o');
}

// Initialize all pointer attributes
/*
void					GameState::_initAllActors(void) {
	// Initialize a list of actors to nullptr
	for (unsigned int i = 0; i < sizeof(_actors) / sizeof(*_actors); i++)
		_actors[i] = nullptr;
}

// Delete all pointer attributes
void					GameState::_deleteAllActors(void) {
	for (unsigned int i = 0; i < sizeof(_actors) / sizeof(*_actors); i++)
		_actors[i] = nullptr;
}

// Set all actors can draw to the input param
void					GameState::_setAllActorsCanDraw(bool bCanDraw) {
	for (unsigned int i = 0; i < sizeof(_actors) / sizeof(*_actors); i++) {
		if (_actors[i]) _actors[i]->setCanDraw(bCanDraw);
	}
}
*/

// Handle game over state for main loop
void				GameState::_handleGameOver(void) {
	static int i = 0;

	if (i == 0) {
		runWinUpdate(false);
		i++;
	}
	//_tickAllActors();
}

// Tick all actors in the actors list
/*
void 				GameState::_tickAllActors(void) {
	for (unsigned int i = 0; i < sizeof(_actors) / sizeof(*_actors); i++) {
		if (_actors[i]) _actors[i]->tick();
	}
}
*/

// The Main window redraw for loading and playing game states
void				GameState::_mainWindowRedraw(void) {
	//_setAllActorsCanDraw(true);
}

// Game over window redraw for when the game is over
void				GameState::_gameOverWindowRedraw(void) {
	//_setAllActorsCanDraw(false);
	mvprintw(HALF_OF_VAL(_winDem.y), HALF_OF_VAL(_winDem.x) - HALF_OF_VAL(strlen("Game Over!")), "Game Over!");
	//mvprintw(HALF_OF_VAL(_winDem.y) + 1, HALF_OF_VAL(_winDem.x) - HALF_OF_VAL(strlen("Player #%d has won!")), "Player #%d has won!", _curPlayer + 1);
}

// Out stream overload for testing
std::ostream		&operator<<(std::ostream &o, GameState const &i) {
	return o << "Game State Info:" << std::endl <<
	"window demensions: " << i.getWinDem() << std::endl <<
	"state: " << i.getCurState() << std::endl;
}
