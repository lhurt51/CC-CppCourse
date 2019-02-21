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

#include "Player.class.hpp"
#include "Game.class.hpp"

// Default Constructor
Player::Player(Board *board, char const sprite) : Actor(Vector2D(board->getPlayerSpawn()), sprite), _board(board), _xDif(0), _bIsTurn(false), _bExitReq(false), _bSpawnPiece(false) {
	return;
}

// Copy constructor
Player::Player(Player const &src) : Actor(src) {
	*this = src;
	return;
}

// Deconstructor
Player::~Player(void) {
	return;
}

// Overloaded equal sign for copy constructor
Player			&Player::operator=(Player const &rhs) {
	if (this != &rhs) {
		// NEED TO IMPROVE!!
		this->_board = rhs.getBoard();
		this->_xDif = rhs.getXDif();
		this->_bExitReq = rhs.getExitReq();
		this->_bSpawnPiece = rhs.getSpawnPiece();
	}
	return *this;
}

// Getters vvvvvvv
Board				*Player::getBoard(void) const {
	return this->_board;
}

int					Player::getXDif(void) const {
	return this->_xDif;
}

bool				Player::getIsTurn(void) const {
	return this->_bIsTurn;
}

bool				Player::getCanInput(void) const {
	return this->_bCanInput;
}

bool				Player::getExitReq(void) const {
	return this->_bExitReq;
}

bool				Player::getSpawnPiece(void) const {
	return this->_bSpawnPiece;
}
// Getters ^^^^^^^

// To move the players position
void				Player::setXDif(int xDif) {
	if (xDif < 0) this->_xDif = 5;
	else if (xDif > 5) this->_xDif = 0;
	else this->_xDif = xDif;
}

// Setting can input
void				Player::setCanInput(bool bCanInput) {
	if (this->_bCanInput == bCanInput) return;
	this->_bCanInput = bCanInput;
}

// If it is not there turn the player will not draw
void				Player::setIsTurn(bool bIsTurn) {
	if (this->_bIsTurn == bIsTurn)
		return;
	else if (bIsTurn == true) {
		this->_bCanDraw = true;
		this->_bCanInput = true;
	} else
		this->_bCanDraw = false;
	this->_bIsTurn = bIsTurn;
	redraw();
}

// Checks does the player need to update
void				Player::shouldUpdate(void) {
	if (this->_bIsTurn) this->redraw();
}

// Spawn a GamePiece if the button has been pressed and col is not full
GamePiece			*Player::createPiece(void) {
	Vector2D tmp = _board->worldToBoard(Vector2D(getPos().getX(), getPos().getY() + 2));

	if (_bSpawnPiece) {
		_bSpawnPiece = false;
		if (!_board->isColFull(tmp.getX())) {
			_bCanInput = false;
			return new GamePiece(_board, _sprite, Vector2D(getPos().getX(), getPos().getY() + 1));
		}
	}
	return nullptr;
}

// On tick handle the players input if it is that players turn
void				Player::tick(void) {
	if (this->_bIsTurn) {
		_handleUserInput(wgetch(Game::getWindow()));
	}
}

// Checks the pos to see if it is within the range on X + 4 with no Y movement
void 				Player::_checkPos(void) {
	if (getPos().getY() != getBoard()->getPlayerSpawn().getY()) _pos.setY(getBoard()->getPlayerSpawn().getY());
	if (getPos().getX() != getBoard()->getPlayerSpawn().getX() + _xDif) _pos.setX(getBoard()->getPlayerSpawn().getX() + _xDif);

}

// Handles the users input as long as the player can draw and can input
void				Player::_handleUserInput(int input) {
	// NEED TO DISABLE MOVEMENT ON PIECE SPAWN!!!
	if (!this->_bCanDraw || !this->_bCanInput) {
		switch(input) {
			case 'q':
				_bExitReq = true;
				break;
			default:
				break;
		}
	} else {
		switch(input) {
			case 'q':
				_bExitReq = true;
				break;
			case KEY_LEFT:
			case 'a':
				setXDif(_xDif - 1);
				move(Vector2D(-1, 0));
				break;
			case KEY_RIGHT:
			case 'd':
				setXDif(_xDif + 1);
				move(Vector2D(1, 0));
				break;
			case 'e':
				_bSpawnPiece = true;
				break;
			default:
				break;
		}
	}
}

// Prints the players attributes
std::ostream	&operator<<(std::ostream &o, Player const &i) {
	// NEEDS IMPROVEMENT!!!
	return o << "Player Info:" << std::endl <<
	"x-dif: " << i.getXDif() << std::endl <<
	"exit req: " << i.getExitReq() << std::endl;
}
