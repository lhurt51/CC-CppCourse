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

static int		conID = 0;

Player::Player(Board *board, char const sprite) : Actor(Vector2D(board->getPlayerSpawn()), sprite), _id(conID++), _board(board), _xDif(0), _bIsTurn(false), _bExitReq(false), _bSpawnPiece(false) {
	return;
}

Player::Player(Player const &src) : Actor(src), _id(src.getPlayerID()) {
	*this = src;
	return;
}

Player::~Player(void) {
	return;
}

Player			&Player::operator=(Player const &rhs) {
	if (this != &rhs) {
		(unsigned int&)this->_id = rhs.getPlayerID();
		this->_board = rhs.getBoard();
		this->_xDif = rhs.getXDif();
		this->_bExitReq = rhs.getExitReq();
		this->_bSpawnPiece = rhs.getSpawnPiece();
	}
	return *this;
}

int					Player::getPlayerID(void) const {
	return this->_id;
}

Board				*Player::getBoard(void) const {
	return this->_board;
}

int					Player::getXDif(void) const {
	return this->_xDif;
}

bool				Player::getIsTurn(void) const {
	return this->_bIsTurn;
}

bool				Player::getExitReq(void) const {
	return this->_bExitReq;
}

bool				Player::getSpawnPiece(void) const {
	return this->_bSpawnPiece;
}

bool				Player::setBoard(Board* board) {
	if (this->_board == board) return false;
	this->_board = board;
	return true;
}

void				Player::setXDif(int xDif) {
	if (xDif < 0) this->_xDif = 5;
	else if (xDif > 5) this->_xDif = 0;
	else this->_xDif = xDif;
}

void				Player::setIsTurn(bool bIsTurn) {
	if (this->_bIsTurn == bIsTurn)
		return;
	else if (bIsTurn == true) {
		this->_bCanDraw = true;
	} else {
		this->_bCanDraw = false;
	}
	this->_bIsTurn = bIsTurn;
}

void				Player::shouldUpdate(void) {
	if (this->_bIsTurn) this->redraw();
}

GamePiece			*Player::createPiece(void) {
	Vector2D tmp = _board->worldToBoard(Vector2D(getPos().getX(), getPos().getY() + 2));

	if (_bSpawnPiece) {
		_bSpawnPiece = false;
		if (!_board->isColFull(tmp.getX()))
			return new GamePiece(_board, _sprite, Vector2D(getPos().getX(), getPos().getY() + 1));
	}
	return nullptr;
}

void				Player::tick(void) {
	if (this->_bIsTurn && this->_bCanDraw) {
		_handleUserInput(wgetch(Game::getWindow()));
	}
}

void 				Player::_checkPos(void) {
	if (getPos().getY() != getBoard()->getPlayerSpawn().getY()) _pos.setY(getBoard()->getPlayerSpawn().getY());
	if (getPos().getX() != getBoard()->getPlayerSpawn().getX() + _xDif) _pos.setX(getBoard()->getPlayerSpawn().getX() + _xDif);

}

void				Player::_handleUserInput(int input) {
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

std::ostream	&operator<<(std::ostream &o, Player const &i) {
	return o << "Player Info:" << std::endl <<
	"id: " << i.getPlayerID() << std::endl <<
	"x-dif: " << i.getXDif() << std::endl <<
	"exit req: " << i.getExitReq() << std::endl;
}
