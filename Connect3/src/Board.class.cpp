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
#include "Board.class.hpp"

Board::Board(void) {

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

char		**Board::getBoard(void) const {
	return this->_board;
}

void		Board::initBoard(void) {
	// Allocate memory for the board base on the type defs
	this->_board = new char *[BOARD_ROW];
	for (int i = BOARD_ROW - 1; i >= 0; i--)
		this->_board[i] = new char[BOARD_COLUMN];
	// Initialize the board to dots
	for (int x = BOARD_ROW - 1; x >= 0; x--) {
		for (int y = BOARD_COLUMN - 1; y >= 0; y--) this->_board[x][y] = '.';
	}
}

bool		Board::addPieceToCol(int col, char c) {
	// Check if the row is full
	if (this->_board[BOARD_ROW - 1][col] != '.') return false;
	// Else look if the row is empty
	else if (this->_board[0][col] == '.') {
		this->_board[0][col] = c;
		return true;
	} else {
		for (int i = BOARD_ROW - 1; i > 0; i--) {
			if(this->_board[i - 1][col] != '.') {
				this->_board[i] = &c;
				return true;
			}
		}
	}
	return false;
}

std::ostream	&operator<<(std::ostream &o, Board const &i) {
	return o << "Board Info:" << std::endl <<
	"board: " << i.getBoard() << std::endl;
}
