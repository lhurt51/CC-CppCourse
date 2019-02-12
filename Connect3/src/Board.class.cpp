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
#include <ncurses.h>
#include "Board.class.hpp"
#include "Vector2D.class.hpp"

Board::Board(void) {
	initBoard();
	return;
}

Board::Board(Board const &src) {
	*this = src;
	return;
}

Board::~Board(void) {
	for (int i = BOARD_ROW - 1; i >= 0; i--) delete[] this->_board[i];
	delete[] this->_board;
	return;
}

Board		&Board::operator=(Board const &rhs) {
	if (this != &rhs) this->_board = rhs.getBoard();
	return *this;
}

bool		Board::getBoardCanUpdate(void) const {
	return this->_bCanUpdate;
}

char		**Board::getBoard(void) const {
	return this->_board;
}

void		Board::initBoard(void) {
	// Allocate memory for the board base on the type defs
	this->_board = new char *[BOARD_ROW];
	for (int i = BOARD_ROW - 1; i >= 0; i--)
		this->_board[i] = new char[BOARD_COLUMN];
	// Initialize the board to dots as empty space
	for (int x = BOARD_ROW - 1; x >= 0; x--) {
		for (int y = BOARD_COLUMN - 1; y >= 0; y--)
			this->_board[x][y] = '.';
	}
}

bool		Board::addPieceToPoint(int row, int col, char c) {
	// Check if the points are on the board then assign the char as
	// long as the boards empty
	if (row >= BOARD_ROW || row < 0 || col >= BOARD_COLUMN || col < 0)
		return false;
	else if(this->_board[row][col] == '.' && (row - 1 >= 0 || this->_board[row - 1][col] != '.')) {
		this->_board[row][col] = c;
		return true;
	}
	return false;
}

bool		Board::isColFull(int col) const {
	// Check if the col is full
	if (this->_board[BOARD_ROW - 1][col] != '.') return true;
	return false;
}

bool		Board::isColEmpty(int col) const {
	// Look if the col is empty
	if (this->_board[0][col] == '.') return true;
	return false;
}

void		Board::tick(Vector2D maxWinDem) {
	_drawBoardToScreen(maxWinDem);
}

void		Board::_drawBoardToScreen(Vector2D maxWinDem) const {
	char msg[] = "543210";

	for (int x = BOARD_ROW + 2; x >= 0; x--) {
		for (int y = BOARD_COLUMN - 1; y >= 0 ; y--) {
			if (x <= BOARD_ROW - 1) {
				mvaddch((int)(maxWinDem.getY() * 0.5f) - y, (int)(maxWinDem.getX() * 0.5f) - x, this->_board[x][y]);
			} else if (x == BOARD_ROW + 2) {
				mvaddch((int)(maxWinDem.getY() * 0.5f) - x, (int)(maxWinDem.getX() * 0.5f) - y, msg[y]);
				if (y - 1 >= 0) mvaddch((int)(maxWinDem.getY() * 0.5f) - x, (int)(maxWinDem.getX() * 0.5f) - (y + 1), msg[y + 1]);
			}
		}
	}
}

std::ostream	&operator<<(std::ostream &o, Board const &i) {
	return o << "Board Info:" << std::endl <<
	"board: " << i.getBoard() << std::endl;
}
