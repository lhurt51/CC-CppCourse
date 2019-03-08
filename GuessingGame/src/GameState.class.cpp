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

#include <time.h>
#include <ncurses.h>
#include <typedefs.hpp>
#include "Vector2D.class.hpp"
#include "Actor.class.hpp"
#include "Player.class.hpp"
#include "GameState.class.hpp"
#include "GameEngine.class.hpp"

// Initializer for window dimensions Constructor
GameState::GameState(Vector2D<uint_fast32_t> const winDem) : _winDem(winDem), _curState(LOADING) {
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
Vector2D<uint_fast32_t> const	GameState::getWinDem(void) const {
	return this->_winDem;
}

State					GameState::getCurState(void) const {
	return this->_curState;
}
// Game State Getters --

// Game State Setters --
void					GameState::setWinDem(Vector2D<uint_fast32_t> const winDem) {
	if (this->_winDem == winDem) return;
	this->_winDem = winDem;
	setCurState(LOADING);
}

State					GameState::setCurState(State curState) {
	static State lastState = STARTING;

	if (this->_curState == curState) return lastState;
	else if (_curState != LOADING) lastState = this->_curState;
	this->_curState = curState;
	return lastState;
}
// Game State Setters --

// Run the main game loop base on the current state
void					GameState::runMainLoop(void) {
	float	fps;
	char	buffer[128];

	switch (_curState) {
		case LOADING:
			setCurState(setCurState(LOADING));
			runWinUpdate(GameEngine::isWindowToSmall(_winDem));
			break;
		case STARTING:
			setCurState(PLAYING);
			break;
		case PLAYING:
			fps = GameEngine::calculateFPS();
			snprintf(buffer, sizeof(buffer), GAME_FPS, fps);
			GameEngine::printMiddle(_winDem, buffer);
			//_tickAllActors();
			break;
		case GAMEOVER:
			_handleGameOver();
			break;
		case EXITING:
			break;
		default:
			break;
	}
}

// Run a window update checking for a too small screen otherwise based off of current state
void					GameState::runWinUpdate(bool const bIsToSmall) {
	clear();
	if (bIsToSmall) {
		//_setAllActorsCanDraw(false);
		GameEngine::printMiddle(_winDem, WIN_2_SMALL_MSG);
	} else {
		switch(_curState) {
			case LOADING:
			case STARTING:
				break;
			case PLAYING:
				_mainWindowRedraw();
				break;
			case GAMEOVER:
				_gameOverWindowRedraw();
				break;
			case EXITING:
				break;
			default:
				break;
		}
		GameEngine::printPos(Vector2D<uint_fast32_t>(HALF_OF_VAL(_winDem.x), 3), GAME_NAME);
	}
	GameEngine::printBorder();
}

void					GameState::handleInput(int input) {
	if (input == 'q') setCurState(EXITING);
	else if (_player) {
		if (input == 'a') _player->moveLeft();
		else _player->stopLeft();
		if (input == 'd') _player->moveRight();
		else _player->stopRight();
	}
}

bool						GameState::runState(void) {
	_draw();
	Actor::tickAllActors();
	if (_player && _player->getPos().x >= _winDem.x) {
		delete _player;
		_player = nullptr;
	}
	if (_curState == EXITING) return false;
	return true;
}

void                        GameState::_draw(void) {
	static Vector2D<uint_fast32_t> lastDem;
	static float fps = GameEngine::calculateFPS();

	if (_winDem != lastDem || fps != GameEngine::calculateFPS()) {
		clear();
		char	buffer[128];

		fps = GameEngine::calculateFPS();
		snprintf(buffer, sizeof(buffer), GAME_FPS, fps);
		Actor::printAllActors();
		GameEngine::printMiddle(_winDem, buffer);
		GameEngine::printBorder();
	}
	lastDem = _winDem;
}

// Handle game over state for main loop
void				GameState::_handleGameOver(void) {
	setCurState(LOADING);
}

// The Main window redraw for loading and playing game states
void				GameState::_mainWindowRedraw(void) {
	//_setAllActorsCanDraw(true);
}

// Game over window redraw for when the game is over
void				GameState::_gameOverWindowRedraw(void) {
	//_setAllActorsCanDraw(false);
	GameEngine::printMiddle(_winDem, GAME_OVER_MSG);
}

// Out stream overload for testing
std::ostream		&operator<<(std::ostream &o, GameState const &i) {
	return o << "Game State Info:" << std::endl <<
	"window demensions: " << i.getWinDem() << std::endl <<
	"state: " << i.getCurState() << std::endl;
}
