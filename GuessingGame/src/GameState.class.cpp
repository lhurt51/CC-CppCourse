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
#include "Input.class.hpp"
#include "Guessing.class.hpp"
#include "GameState.class.hpp"
#include "GameEngine.class.hpp"

// Initializer for window dimensions Constructor
GameState::GameState(Vector2D<uint_fast32_t> const winDem) : _winDem(winDem), _curState(STARTING), _menuHandler(nullptr), _input(nullptr), _guessInt(nullptr), _guessChar(nullptr) {
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
	_deleteInput();
	_deleteGuessing();
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
	else if (_curState != LOADING && _curState != ERROR && _curState != INPUTING)
		lastState = this->_curState;
	this->_curState = curState;
	return lastState;
}

// Handle the input for all the actors that require input
void							GameState::handleInput(int input) {
	if (input == '`') setCurState(EXITING);
	if (_menuHandler) {
		if (_menuHandler->getIsHorizontal()) {
			if (input == 'a') _menuHandler->decreaseIndexItem();
			if (input == 'd') _menuHandler->increaseIndexItem();
		} else {
			if (input == 'w') _menuHandler->decreaseIndexItem();
			if (input == 's') _menuHandler->increaseIndexItem();
		}
		if (input == '\n') _execMenuInput();
	} else if (_input) {
		if (input == '\n') {
			_input->setIsTyping();
		} else if (std::isalpha(input) || std::isdigit(input)) {
			_input->addInputToString(input);
		} else {
			_input->finnishInput();
		}
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
	Actor::tickAllActors();
	_draw();
	return true;
}

void							GameState::_execMenuInput(void) {
	_menuHandler->doExecute();
	if ((_guessInt || _guessChar) && bIsPlaying) {
		if (_guessChar) {
			if (_menuHandler->getItemIndex() == 0) {
				_guessChar->setShouldIncrease();
			} else {
				_guessChar->setShouldDecrease();
			}
		}
		if (_guessInt) {
			if (_menuHandler->getItemIndex() == 0) {
				_guessInt->setShouldIncrease();
			} else {
				_guessInt->setShouldDecrease();
			}
		}
	}
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
			fps = GameEngine::calculateFPS();
			GameEngine::printPos(Vector2D<uint_fast32_t>(10, 1), GAME_FPS + std::to_string(fps));
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
	} else if (_input && _input->getIsTyping()) {
		Actor::setAllActorsCanDraw(true);
		setCurState(INPUTING);
	} else {
		Actor::setAllActorsCanDraw(true);
		setCurState(setCurState(LOADING));
	}
}

// Handle the starting state update
void							GameState::_handleStartingState(void) {
	static bool first = true;

	_deleteInput();
	_deleteGuessing();
	if ((first && _menuHandler) || _checkStateChange()) {
		_deleteMenuHandler();
		first = false;
	}
	_initMenuHandler(MAIN_MENU_TITLE, { MAIN_MENU_START_B, MAIN_MENU_TEST_B, MAIN_MENU_EXIT_B }, false);
}

// Handle input state update
void							GameState::_handleInputingState(void) {
	_deleteGuessing();
	_deleteMenuHandler();
	_initInput();
}

// Handle playing state update
void							GameState::_handlePlayingState(void) {
	static bool first = true;

	if ((first && _menuHandler) || _checkStateChange()) {
		_deleteMenuHandler();
		first = false;
	}
	_initGuessing();
	_initMenuHandler(IN_GAME_MENU_TITLE, { IN_GAME_MENU_INC_B, IN_GAME_MENU_DEC_B }, true);
}

void							GameState::_handleTestingState(void) {
	static bool first = true;

	if ((first && _menuHandler) || _checkStateChange()) {
		_deleteMenuHandler();
		first = false;
	}
	_initGuessing();
	_initMenuHandler(TESTING_MENU_TITLE, { TESTING_MENU_EXIT_B }, true);
}

// Handle game over state update
void 							GameState::_handleGameOverState(void) {
	static bool first = true;

	if ((first && _menuHandler) || _checkStateChange()) {
		_deleteMenuHandler();
		first = false;
	}
	_initMenuHandler("GAME OVER", { "Back To Main Menu" }, true);
}

// Handle error state update
void 							GameState::_handleErrorState(void) {
	return;
}

// Handle the exiting state update
void							GameState::_handleExitingState(void) {
	_deleteMenuHandler();
	_deleteInput();
	_deleteGuessing();
}

void							GameState::_initMenuHandler(std::string const title, std::vector<std::string> const items, bool bIsHorizontal) {
	if (!_menuHandler)
		_menuHandler = new MenuHandler(*this, title, items, bIsHorizontal);
}

void							GameState::_initInput(void) {
	if (!_input)
		_input = new Input(*this, Vector2D<uint_fast32_t> (HALF_OF_VAL(_winDem.x), HALF_OF_VAL(_winDem.y)));
}

void							GameState::_initGuessing(void) {
	const std::vector<char> charInitList = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z' };
	std::vector<unsigned> intInitList;

	if (!_guessInt && !_guessChar && _input && !_input->getIsTyping()) {
		if (_input->getIsChar()) {
			_guessChar = new Guessing<char>(*this, charInitList, std::toupper(_input->getSprite()[0]));
		} else {
			for (unsigned i = 0; i < 1001; i++)
				intInitList.push_back(i);
			_guessInt = new Guessing<unsigned>(*this, intInitList, std::max(0, std::min(std::stoi(_input->getSprite()), 1000)));
		}
	}
	_deleteInput();
}

// Delete the menu handler as long as its allocated
void							GameState::_deleteMenuHandler(void) {
	if (_menuHandler) {
		delete _menuHandler;
		_menuHandler = nullptr;
	}
}

// Delete the input as long as its allocated
void							GameState::_deleteInput(void) {
	if (_input) {
		delete _input;
		_input = nullptr;
	}
}

void							GameState::_deleteGuessing(void) {
	if (_guessInt) {
		delete _guessInt;
		_guessInt = nullptr;
	}
	if (_guessChar) {
		delete _guessChar;
		_guessChar = nullptr;
	}
}

// Out stream overload for testing
std::ostream					&operator<<(std::ostream &o, GameState const &i) {
	return o << "Game State Info:" << std::endl <<
	"window demensions: " << i.getWinDem() << std::endl <<
	"state: " << i.getCurState() << std::endl;
}
