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
	Vector2D tmp;
	int x, y;

	getmaxyx(this->_window, y, x);
	tmp = Vector2D(x, y);
	if (tmp.getX() < Game::minWinDem.getX()) tmp.setX(Game::minWinDem.getX());
	if (tmp.getY() < Game::minWinDem.getY()) tmp.setY(Game::minWinDem.getY());
	resizeterm(tmp.getY(), tmp.getX());
	if (this->_maxWinDem == tmp) return false;
	this->_maxWinDem = tmp;
	return true;
}

void			Game::run(void) {
	bool updateWin;

	while (1) {
		if (wgetch(this->_window) == 'q') break;
		updateWin = updateWinDem();
		if (updateWin) {
			clear();
			char msg[] = "Should be in the middle";
			mvprintw(this->_maxWinDem.getY() * 0.5f, (this->_maxWinDem.getX() - std::strlen(msg)) * 0.5f, "%s", msg);
			mvprintw(this->_maxWinDem.getY() - 7, 5, "Width: %d and Height: %d", this->_maxWinDem.getX(), this->_maxWinDem.getY());
			wborder(this->_window, '|', '|', '-', '-', 'o', 'o', 'o', 'o');
		}
		wrefresh(this->_window);
	}
	return;
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
	"Window adr: " << i.getWindow() << std::endl <<
	"Window demension: " << i.getWinMaxDem() << std::endl;
}
