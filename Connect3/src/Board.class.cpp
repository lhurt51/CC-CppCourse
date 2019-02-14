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
	deleteBoard();
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
	// Allocate memory for the board base on my macros
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
	if (IS_SIZE_INVALID(row, col) || isColFull(col))
		return false;
	else if(isColEmpty(col) || (this->_board[row][col] == '.' && this->_board[row - 1][col] != '.'))
		this->_board[row][col] = c;
	else
		return false;
	return true;
}

void		Board::deleteBoard(void) {
	// Delete the memory allocated to board
	for (int i = BOARD_ROW - 1; i >= 0; i--)
		delete[] this->_board[i];
	delete[] this->_board;
}

bool		Board::isColFull(int col) const {
	// Check if the col is full
	if (IS_COL_INVALID(col))
		return false;
	else if (this->_board[BOARD_ROW - 1][col] != '.')
		return true;
	else
		return false;
}

bool		Board::isColEmpty(int col) const {
	// Look if the col is empty
	if (IS_COL_INVALID(col))
		return false;
	else if (this->_board[0][col] == '.')
		return true;
	else
		return false;
}

void		Board::tick(Vector2D maxWinDem) {
	_drawBoardToScreen(maxWinDem);
}

void		Board::_drawBoardToScreen(Vector2D maxWinDem) const {
	char msg[] = "543210";

	for (int y = BOARD_ROW + 2; y >= 0; y--) {
		for (int x = BOARD_COLUMN - 1; x >= 0 ; x--) {
			if (!IS_ROW_INVALID(y))
				mvaddch(HALF_OF_VAL(maxWinDem.getY()) - y, HALF_OF_VAL(maxWinDem.getX()) - x, this->_board[y][x]);
			else if (y == BOARD_ROW + 2)
				mvaddch(HALF_OF_VAL(maxWinDem.getY()) - y, HALF_OF_VAL(maxWinDem.getX()) - x, msg[x]);
			else if (y == BOARD_ROW + 1 && x == BOARD_COLUMN - 1)
				Player::setSpawnLoc(Vector2D(HALF_OF_VAL(maxWinDem.getX()) - x, HALF_OF_VAL(maxWinDem.getY()) - y));
		}
	}
}

std::ostream	&operator<<(std::ostream &o, Board const &i) {
	return o << "Board Info:" << std::endl <<
	"Can Update?: " << i.getBoardCanUpdate() << std::endl <<
	"board: " << i.getBoard() << std::endl;
}
