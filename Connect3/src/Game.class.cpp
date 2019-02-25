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

#include "Game.class.hpp"
#include "GameState.class.hpp"

// Initializing the static window to null
WINDOW			*Game::_window = nullptr;

// Initializing the window with ncurses
Game::Game(void) {
	Game::_window = initscr();
	cbreak();
	noecho();
	clear();
	wrefresh(Game::_window);
	keypad(Game::_window, true);
	nodelay(Game::_window, true);
	curs_set(0);
	/* Because I do not use colors yet --
	if (!has_colors()) {
		std::cout << "Error: Terminal does not support color" << std::endl;
		return;
	}
	start_color();
	*/
	return;
}

// Copy constructor --
Game::Game(Game const &src) {
	*this = src;
	return;
}

// Deconstructor --
Game::~Game(void) {
	destroyWin();
	return;
}

// Overload equal sign for copy constructor
Game			&Game::operator=(Game const &rhs) {
	if (this != &rhs) {
		Game::_window = rhs.getWindow();
		this->_maxWinDem = rhs.getWinMaxDem();
	}
	return *this;
}

// Getters --
WINDOW*			Game::getWindow(void) {
	return Game::_window;
}

Vector2D		Game::getWinMaxDem(void) const {
	return this->_maxWinDem;
}

// Update the win demension
bool        	Game::updateWinDem(void) {
	unsigned int x, y;

	getmaxyx(Game::_window, y, x);
	if (this->_maxWinDem == Vector2D(x, y)) return false;
	this->_maxWinDem = Vector2D(x, y);
	return true;
}

// Run the window loop
void			Game::run(void) {
	GameState *gameState;

	clear();
	updateWinDem();
	gameState = new GameState(_maxWinDem);
	do {
		if (gameState->bShouldExit()) break;
		if (updateWinDem() || gameState->getCurState() == LOADING) {
			gameState->runWinUpdate(_maxWinDem, isWindowToSmall());
		} else {
			gameState->runMainLoop();
		}
		wrefresh(Game::_window);
	} while(true);
	delete gameState;
	return;
}

// Check the win demensions
bool            Game::isWindowToSmall(void) {
	if (this->_maxWinDem > Vector2D(MIN_WIN_SIZE))
		return false;
	/* Commented out because resizeterm func does not currently work
	else if (this->_maxWinDem.getX() <= MIN_WIN_SIZE && this->_maxWinDem.getY() > MIN_WIN_SIZE)
		resizeterm(this->_maxWinDem.getY(), Game::minWinDem.getX());
	else if (this->_maxWinDem.getY() <= MIN_WIN_SIZE && this->_maxWinDem.getX() > MIN_WIN_SIZE)
		resizeterm(Game::minWinDem.getY(), this->_maxWinDem.getX());
	else
		resizeterm(Game::minWinDem.getY(), Game::minWinDem.getX());
	*/
	return true;
}

// Destroy the window and clear any artifacts
void        	Game::destroyWin(void) {
	wborder(Game::_window, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
	wrefresh(Game::_window);
	delwin(Game::_window);
	endwin();
	Game::_window = NULL;
	return;
}

// To print out all of the games attributes
std::ostream	&operator<<(std::ostream &o, Game const &i) {
	return o << "Game Thread Info:" << std::endl <<
	"Window addr: " << i.getWindow() << std::endl <<
	"Window demension: " << i.getWinMaxDem() << std::endl;
}
