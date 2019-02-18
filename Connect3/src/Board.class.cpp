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

#include "Board.class.hpp"
#include "Player.class.hpp"

Board::Board(void) : Actor(Vector2D(DEFAULT_SPAWN), ' '), _playerSpawn(Vector2D(DEFAULT_SPAWN)) {
	initBoard();
	return;
}

Board::Board(Board const &src) : Actor(src) {
	*this = src;
	return;
}

Board::~Board(void) {
	deleteBoard();
	return;
}

Board		&Board::operator=(Board const &rhs) {
	if (this != &rhs) {
		this->_board = rhs.getBoard();
		this->_playerSpawn = rhs.getPlayerSpawn();
	}
	return *this;
}

char		**Board::getBoard(void) const {
	return this->_board;
}

Vector2D	Board::getPlayerSpawn(void) const {
	return this->_playerSpawn;
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

void		Board::updateBoard(int col) {
	if (!IS_COL_INVALID(col)) _drawBoardColToScreen(false, col);
	else _drawBoardToScreen(false);
}

void		Board::tick(void) {
	this->_playerSpawn = Vector2D(this->getPos().getX() - (BOARD_COLUMN - 1), this->getPos().getY() - (BOARD_ROW + 1));
	if (!this->_bCanDraw) return;
	redraw();
}

void 		Board::_checkPos(void) {
	return;
}

void		Board::_draw(void) const {
	_drawBoardToScreen(false);
	return;
}

void		Board::_clear(void) const {
	_drawBoardToScreen(true);
	return;
}

void		Board::_drawBoardToScreen(bool clear) const {
	char msg[] = "543210";

	for (int y = BOARD_ROW + 3; y >= 0; y--) {
		for (int x = BOARD_COLUMN - 1; x >= 0 ; x--) {
			if (!IS_ROW_INVALID(y))
				mvaddch(this->getPos().getY() - y, this->getPos().getX() - x, (clear) ? ' ' : this->_board[y][x]);
			else if (y == BOARD_ROW + 3)
				mvaddch(this->getPos().getY() - y, this->getPos().getX() - x, (clear) ? ' ' : msg[x]);
		}
	}
}

void			Board::_drawBoardColToScreen(bool clear, int col) const {
	if (IS_COL_INVALID(col)) return;
	for (int y = BOARD_ROW - 1; y >= 0; y--) {
		mvaddch(this->getPos().getY() - y, this->getPos().getX() - col, (clear) ? ' ' : this->_board[y][col]);
	}
}

std::ostream	&operator<<(std::ostream &o, Board const &i) {
	return o << "Board Info:" << std::endl <<
	"player spawn" << i.getPlayerSpawn() << std::endl <<
	"board: " << i.getBoard() << std::endl;
}
