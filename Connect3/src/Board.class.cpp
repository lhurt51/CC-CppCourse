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

#include "Board.class.hpp"
#include "Player.class.hpp"
#include "Game.class.hpp"

// Default constructor
Board::Board(void) : Actor(Vector2D(DEFAULT_SPAWN), ' '), _bHasWon(false), _winningC(' '), _playerSpawn(Vector2D(DEFAULT_SPAWN)) {
	initBoard();
	return;
}

// Pos initializer constructor
Board::Board(Vector2D pos) : Actor(Vector2D(pos), ' '), _playerSpawn(Vector2D(DEFAULT_SPAWN)) {
	initBoard();
	return;
}

// Copy constructor
Board::Board(Board const &src) : Actor(src) {
	*this = src;
	return;
}

// Deconstructor
Board::~Board(void) {
	deleteBoard();
	return;
}

// Equal sign operator overload
Board		&Board::operator=(Board const &rhs) {
	if (this != &rhs) {
		this->_bHasWon = rhs.getHasWon();
		this->_winningC = rhs.getWinningChar();
		this->_board = rhs.getBoard();
		this->_playerSpawn = rhs.getPlayerSpawn();
	}
	return *this;
}

// All Board Getters --
bool		Board::getHasWon(void) const {
	return this->_bHasWon;
}

char		Board::getWinningChar(void) const {
	return this->_winningC;
}

char		**Board::getBoard(void) const {
	return this->_board;
}

Vector2D	Board::getPlayerSpawn(void) const {
	return this->_playerSpawn;
}
// All Board Getters --

// Board Initializer
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

// Add a piece to the board
bool		Board::addPieceToPoint(int row, int col, char c) {
	// Check if the points are on the board then assign the char as
	// long as the boards empty
	if (IS_SIZE_INVALID(row, col) || isColFull(col))
		return false;
	else if((isColEmpty(col) && row == 0) || (this->_board[row][col] == '.' && this->_board[row - 1][col] != '.'))
		this->_board[row][col] = c;
	else
		return false;
	checkForWinGame(Vector2D(col, row), c);
	return true;
}

// Delete the boards memory
void		Board::deleteBoard(void) {
	// Delete the memory allocated to board
	for (int i = BOARD_ROW - 1; i >= 0; i--)
		delete[] this->_board[i];
	delete[] this->_board;
}

// Check if board col is full
bool		Board::isColFull(int col) const {
	// Check if the col is full
	if (IS_COL_INVALID(col))
		return false;
	else if (this->_board[BOARD_ROW - 1][col] != '.')
		return true;
	else
		return false;
}

// Check if the whole board is full
bool		Board::isBoardFull(void) const {
	int counter = 0;

	for (int i = BOARD_COLUMN - 1; i >= 0; i--) {
		if (isColFull(i)) counter++;
	}
	return (counter == BOARD_COLUMN);
}

// Check if board col is empty
bool		Board::isColEmpty(int col) const {
	// Look if the col is empty
	if (IS_COL_INVALID(col))
		return false;
	else if (this->_board[0][col] == '.')
		return true;
	else
		return false;
}

// World to board cordinate conversion
Vector2D	Board::worldToBoard(Vector2D world) {
	Vector2D board = Vector2D(getPos().getX() - world.getX(), getPos().getY() - world.getY());

	// Changing the screen cords to a board pos as long as its valid
	if (IS_SIZE_INVALID(board.getY(), board.getX()))
		return Vector2D(-1);
	else
		return board;
}

// Check for win game status
void		Board::checkForWinGame(Vector2D pos, char c) {
	int i = 0;

	// There is two better ways to do this but this is a sure fire method
	// Making sure that the spot is valid and the char was placed
	if (IS_SIZE_INVALID(pos.getY(), pos.getX()) || _board[pos.getY()][pos.getX()] != c) return;
	// Checking the x + 1 then x + 2
	if (!IS_COL_INVALID(pos.getX() + 1) && _board[pos.getY()][pos.getX() + 1] == c) {
		i++;
		if (!IS_COL_INVALID(pos.getX() + 2) && _board[pos.getY()][pos.getX() + 2] == c) {
			this->_bHasWon = true;
			this->_winningC = c;
			return;
		}
	}
	// Checking x - 1 then x - 2
	if (!IS_COL_INVALID(pos.getX() - 1) && _board[pos.getY()][pos.getX() - 1] == c) {
		if (++i == 2 || (!IS_COL_INVALID(pos.getX() - 2) && _board[pos.getY()][pos.getX() - 2] == c)) {
			this->_bHasWon = true;
			this->_winningC = c;
			return;
		}
	}
	// Reset I because Y is not in the same line
	i = 0;
	// Checking y + 1 then y + 2
	if (!IS_ROW_INVALID(pos.getY() + 1) && _board[pos.getY() + 1][pos.getX()] == c) {
		i++;
		if (!IS_ROW_INVALID(pos.getY() + 2) && _board[pos.getY() + 2][pos.getX()] == c) {
			this->_bHasWon = true;
			this->_winningC = c;
			return;
		}
	}
	// Checking y - 1 then y - 2
	if (!IS_ROW_INVALID(pos.getY() - 1) && _board[pos.getY() - 1][pos.getX()] == c) {
		if (++i == 2 || (!IS_ROW_INVALID(pos.getY() - 2) && _board[pos.getY() - 2][pos.getX()] == c)) {
			this->_bHasWon = true;
			this->_winningC = c;
			return;
		}
	}
}

void		Board::tick(void) {
	return;
}

// Actor virtual overrides --
void 		Board::_checkPos(void) {
	this->_playerSpawn = Vector2D(this->getPos().getX() - (BOARD_COLUMN - 1), this->getPos().getY() - (BOARD_ROW + 1));
}

void		Board::_draw(void) const {
	_drawBoardToScreen(false);
}

void		Board::_clear(void) const {
	_drawBoardToScreen(true);
}
// Actor virtual overrides --

// Drawing each col to the screen
void		Board::_drawBoardToScreen(bool clear) const {
	for (int x = BOARD_COLUMN - 1; x >= 0 ; x--) {
		_drawBoardColToScreen(clear, x);
	}
}

// Drawing or clearing each col to the screen including the header
void			Board::_drawBoardColToScreen(bool clear, int col) const {
	char msg[] = "543210";

	if (IS_COL_INVALID(col)) return;
	for (int y = BOARD_ROW + 3; y >= 0; y--) {
		if (!IS_ROW_INVALID(y))
			_printChar(clear,  this->_board[y][col], this->getPos().getX() - col, this->getPos().getY() - y);
		else if (y == BOARD_ROW + 3)
			_printChar(clear, msg[col], this->getPos().getX() - col, this->getPos().getY() - y);
	}
}

// Print or clear each char based on what is currently there
void			Board::_printChar(bool clear, char c, int x, int y) const {
	chtype test;

	test = mvwinch(Game::getWindow(), y, x);
	if (clear == false && (char)test == c) return;
	else if (clear == true && (char)test != c) return;
	mvaddch(y, x, (clear) ? ' ' : c);
}

// Output overload for testing
std::ostream	&operator<<(std::ostream &o, Board const &i) {
	return o << "Board Info:" << std::endl <<
	"player spawn" << i.getPlayerSpawn() << std::endl <<
	"board: " << i.getBoard() << std::endl;
}
