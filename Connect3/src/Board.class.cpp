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
#include "Player.class.hpp"

Board::Board(void) : _bCanUpdate(true) {
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
	if (this != &rhs) {
		this->_bCanUpdate = rhs.getBoardCanUpdate();
		this->_board = rhs.getBoard();
	}
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
	for (int y = BOARD_ROW - 1; y >= 0; y--) {
		for (int x = BOARD_COLUMN - 1; x >= 0; x--)
			this->_board[y][x] = '.';
	}
}

bool		Board::addPieceToPoint(int row, int col, char c) {
	// Check if the points are on the board then assign the char as
	// long as the boards empty
	if (row >= BOARD_ROW - 1|| row < 0 || col >= BOARD_COLUMN - 1 || col < 0)
		return false;
	else if(this->_board[row][col] == '.' && (row == 0 || this->_board[row - 1][col] != '.'))
		this->_board[row][col] = c;
	else
		return false;
	return true;
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

	for (int y = BOARD_ROW + 2; y >= 0; y--) {
		for (int x = BOARD_COLUMN - 1; x >= 0 ; x--) {
			if (y <= BOARD_ROW - 1)
				mvaddch((int)(maxWinDem.getY() * 0.5f) - y, (int)(maxWinDem.getX() * 0.5f) - x, this->_board[y][x]);
			else if (y == BOARD_ROW + 2)
				mvaddch((int)(maxWinDem.getY() * 0.5f) - y, (int)(maxWinDem.getX() * 0.5f) - x, msg[x]);
			else if (y == BOARD_ROW + 1 && x == 0) {
				Player::setSpawnLoc(Vector2D((int)(maxWinDem.getY() * 0.5f) - y, (int)(maxWinDem.getX() * 0.5f) - x));
			}
		}
	}
}

std::ostream	&operator<<(std::ostream &o, Board const &i) {
	return o << "Board Info:" << std::endl <<
	"Can Update?: " << i.getBoardCanUpdate() << std::endl <<
	"board: " << i.getBoard() << std::endl;
}
