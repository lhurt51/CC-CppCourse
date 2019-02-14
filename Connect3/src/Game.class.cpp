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
* Only need to connect verticle and horizontal
* Use a board of 5 by 6 with header for the column number
* Use ASCII graphics
*
******************************************************************************/

#include <typedefs.hpp>
#include "Game.class.hpp"
#include "Board.class.hpp"

Vector2D		Game::minWinDem = Vector2D(MIN_WIN_SIZE);

Game::Game(void) : _window(initscr()) {
	cbreak();
	noecho();
	clear();
	wrefresh(this->_window);
	keypad(this->_window, true);
	nodelay(this->_window, true);
	curs_set(0);
	if (!has_colors()) {
		std::cout << "Error: Terminal does not support color" << std::endl;
		this->~Game();
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
	if (this != &rhs) this->_window = rhs.getWindow();
	return *this;
}

WINDOW*			Game::getWindow(void) const {
	return this->_window;
}

Vector2D		Game::getWinMaxDem(void) const {
	return this->_maxWinDem;
}

bool        	Game::updateWinDem(void) {
	int x, y;

	getmaxyx(this->_window, y, x);
	if (this->_maxWinDem == Vector2D(x, y)) return false;
	this->_maxWinDem = Vector2D(x, y);
	return true;
}

void			Game::run(void) {
	Board board;
	char msg[] = "Error!! Window too small.";

	board.addPieceToPoint(-3, 7, 'a');
	board.addPieceToPoint(0, 5, 'b');
	board.addPieceToPoint(0, 2, 'c');
	board.addPieceToPoint(1, 1, 'd');
	board.addPieceToPoint(0, 1, 'e');
	board.addPieceToPoint(1, 2, 'f');
	board.addPieceToPoint(3, 2, 'g');
	do {
		if (wgetch(this->_window) == 'q') break;
		if (updateWinDem()) {
			clear();
			if (isWindowToSmall()) {
				mvprintw((int)(this->_maxWinDem.getY() * 0.5f), (int)((this->_maxWinDem.getX() - strlen(msg)) * 0.5f),"%s",msg);
			} else {
				board.tick(this->_maxWinDem);
				mvprintw(this->_maxWinDem.getY() - 5, 5, "Width: %d and Height: %d", this->_maxWinDem.getX(), this->_maxWinDem.getY());
				wborder(this->_window, '|', '|', '-', '-', 'o', 'o', 'o', 'o');
			}
		}
		wrefresh(this->_window);
	} while(true);
	return;
}

bool            Game::isWindowToSmall(void) {
	if (this->_maxWinDem > Game::minWinDem)
		return false;
	/* Commented out because resizeterm func does not currently work
	else if (this->_maxWinDem.getX() <= Game::minWinDem.getX() && this->_maxWinDem.getY() > Game::minWinDem.getY())
		resizeterm(this->_maxWinDem.getY(), Game::minWinDem.getX());
	else if (this->_maxWinDem.getY() <= Game::minWinDem.getY() && this->_maxWinDem.getX() > Game::minWinDem.getX())
		resizeterm(Game::minWinDem.getY(), this->_maxWinDem.getX());
	else
		resizeterm(Game::minWinDem.getY(), Game::minWinDem.getX());
	*/
	return true;
}

void        	Game::destroyWin(void) {
	wborder(this->_window, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
	wrefresh(this->_window);
	delwin(this->_window);
	endwin();
	return;
}

std::ostream	&operator<<(std::ostream &o, Game const &i) {
	return o << "Game Thread Info:" << std::endl <<
	"Window addr: " << i.getWindow() << std::endl <<
	"Window demension: " << i.getWinMaxDem() << std::endl;
}
