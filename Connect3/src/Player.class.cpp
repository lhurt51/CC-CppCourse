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

Player::Player(Board *board, char const sprite) : Actor(Vector2D(DEFAULT_SPAWN), sprite), _id(conID++), _board(board), _xDif(0), _bExitReq(false), _bSpawnPiece(false), _updatePos(false) {
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
		this->_updatePos = rhs.getUpdatePos();
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

bool				Player::getExitReq(void) const {
	return this->_bExitReq;
}

bool				Player::getSpawnPiece(void) const {
	return this->_bSpawnPiece;
}

bool				Player::getUpdatePos(void) const {
	return this->_updatePos;
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

void				Player::setUpdatePos(bool bShouldUpdate) {
	if (this->_updatePos == bShouldUpdate) return;
	this->_updatePos = bShouldUpdate;
}

GamePiece			*Player::createPiece(void) {
	Vector2D tmp = _board->worldToBoard(getPos());

	if (this->_bSpawnPiece || !_board->isColFull(tmp.getX()))
		return new GamePiece(this->_board, this->_sprite, this->getPos());
	return NULL;
}

void				Player::tick(void) {
	if (this->_updatePos) {
		this->redraw();
		this->_updatePos = false;
	}
	int input = wgetch(Game::getWindow());
	if (this->_checkInput(input)) this->_handleUserInput(input);
}

void 				Player::_checkPos(void) {
	if (getPos().getY() != getBoard()->getPlayerSpawn().getY()) _pos.setY(getBoard()->getPlayerSpawn().getY());
	if (getPos().getX() != getBoard()->getPlayerSpawn().getX() + _xDif) _pos.setX(getBoard()->getPlayerSpawn().getX() + _xDif);

}

bool 				Player::_checkInput(int input) {
	switch (input) {
		case 'q':
		case KEY_LEFT:
		case 'a':
		case KEY_RIGHT:
		case 'd':
			return true;
		default:
			return false;
	}
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
	"exit req: " << i.getExitReq() << std::endl <<
	"update pos?: " << i.getUpdatePos() << std::endl;
}
