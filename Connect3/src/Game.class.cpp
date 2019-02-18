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
#include "Board.class.hpp"
#include "Player.class.hpp"
#include "GamePiece.class.hpp"

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
	if (this != &rhs) Game::_window = rhs.getWindow();
	return *this;
}

WINDOW*			Game::getWindow(void) {
	return Game::_window;
}

Vector2D		Game::getWinMaxDem(void) const {
	return this->_maxWinDem;
}

bool        	Game::updateWinDem(void) {
	int x, y;

	getmaxyx(Game::_window, y, x);
	if (this->_maxWinDem == Vector2D(x, y)) return false;
	this->_maxWinDem = Vector2D(x, y);
	return true;
}

void			Game::run(void) {
	Board board;
	Player player1(&board, 'G');
	GamePiece piece(&board, 'X', Vector2D(15, 15));
	char msg[] = "Error! Window too small";

	board.addPieceToPoint(-3, 7, 'a');
	board.addPieceToPoint(0, 5, 'b');
	board.addPieceToPoint(0, 2, 'c');
	board.addPieceToPoint(1, 1, 'd');
	board.addPieceToPoint(0, 1, 'e');
	board.addPieceToPoint(1, 2, 'f');
	board.addPieceToPoint(3, 2, 'g');
	do {
		if (player1.getExitReq()) break;
		if (updateWinDem()) {
			clear();
			if (isWindowToSmall()) {
				board.setCanDraw(false);
				player1.setCanDraw(false);
				piece.setCanDraw(false);
				mvprintw(HALF_OF_VAL(this->_maxWinDem.getY()), HALF_OF_VAL(this->_maxWinDem.getX()) - HALF_OF_VAL(strlen(msg)),"%s",msg);
			} else {
				board.setCanDraw(true);
				player1.setCanDraw(true);
				piece.setCanDraw(true);
				board.setPos(Vector2D(HALF_OF_VAL(this->_maxWinDem.getX()), HALF_OF_VAL(this->_maxWinDem.getY())));
				player1.setUpdatePos(true);
				piece.setStartPos(player1.getPos());
				mvprintw(this->_maxWinDem.getY() - 5, 5, "Width: %d and Height: %d", this->_maxWinDem.getX(), this->_maxWinDem.getY());
			}
			wborder(Game::_window, '|', '|', '-', '-', 'o', 'o', 'o', 'o');
		} else {
			board.tick();
			player1.tick();
			piece.setStartPos(player1.getPos());
			piece.tick();
			Vector2D tmp = board.worldToBoard(piece.getPos());
			mvprintw(this->_maxWinDem.getY() - 6, 5, "Piece board pos: %d, %d", tmp.getX(), tmp.getY());
		}
		wrefresh(Game::_window);
	} while(true);
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
