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

WINDOW			*Game::_window = NULL;

Game::Game(void) {
	Game::_window = initscr();
	cbreak();
	noecho();
	clear();
	wrefresh(Game::_window);
	keypad(Game::_window, true);
	nodelay(Game::_window, true);
	curs_set(0);
	if (!has_colors()) {
		std::cout << "Error: Terminal does not support color" << std::endl;
		return;
	}
	start_color();
	return;
}

Game::Game(Game const &src) {
	*this = src;
	return;
}

Game::~Game(void) {
	destroyWin();
	return;
}

Game			&Game::operator=(Game const &rhs) {
	if (this != &rhs) {
		Game::_window = rhs.getWindow();
		this->_maxWinDem = rhs.getWinMaxDem();
	}
	return *this;
}

WINDOW*			Game::getWindow(void) {
	return Game::_window;
}

Vector2D		Game::getWinMaxDem(void) const {
	return this->_maxWinDem;
}

bool        	Game::updateWinDem(void) {
	unsigned int x, y;

	getmaxyx(Game::_window, y, x);
	if (this->_maxWinDem == Vector2D(x, y)) return false;
	this->_maxWinDem = Vector2D(x, y);
	return true;
}

void			Game::run(void) {
	GameState *gameState;
	
	clear();
	updateWinDem();
	gameState = new GameState(_maxWinDem);
	do {
		if (gameState->bShouldExit()) break;
		if (updateWinDem()) {
			gameState->setWinDem(_maxWinDem);
			gameState->runWinUpdate(isWindowToSmall());
		} else {
			gameState->runMainLoop();
		}
		wrefresh(Game::_window);
	} while(true);
	delete gameState;
	return;
}

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

void        	Game::destroyWin(void) {
	wborder(Game::_window, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
	wrefresh(Game::_window);
	delwin(Game::_window);
	endwin();
	Game::_window = NULL;
	return;
}

std::ostream	&operator<<(std::ostream &o, Game const &i) {
	return o << "Game Thread Info:" << std::endl <<
	"Window addr: " << i.getWindow() << std::endl <<
	"Window demension: " << i.getWinMaxDem() << std::endl;
}
