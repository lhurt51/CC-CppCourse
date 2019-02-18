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

#include "GamePiece.class.hpp"

GamePiece::GamePiece(Board *board, char const sprite, Vector2D pos) : Actor(pos, sprite), _bCanClear(false) , _startPos(pos), _board(board) {
	return;
}

GamePiece::GamePiece(GamePiece const &src) : Actor(src), _startPos(src.getStartPos()) {
	*this = src;
	return;
}

GamePiece::~GamePiece(void) {
	return;
}

GamePiece	&GamePiece::operator=(GamePiece const &rhs) {
	if (this != &rhs) {
		(Vector2D&)this->_startPos = rhs.getStartPos();
		this->_board = rhs.getBoard();
	}
	return *this;
}

Vector2D	GamePiece::getStartPos(void) const {
	return this->_startPos;
}

Board		*GamePiece::getBoard(void) const {
	return this->_board;
}

bool		GamePiece::getCanClear(void) const {
	return this->_bCanClear;
}

bool		GamePiece::setStartPos(Vector2D vec) {
	if (this->_startPos == vec) return false;
	(Vector2D&)this->_startPos = vec;
	return true;
}

void		GamePiece::tick(void) {
	static int frame = 0;

	if (frame % 25000 == 0) {
		//if (this->_board->addPieceToPoint())
		move(Vector2D(0, 1));
		if (frame > 100) this->_bCanClear = true;
	} else if (frame > 25000) {
		frame = 1;
	}
	redraw();
	frame++;
}

void 		GamePiece::_checkPos(void) {
	if (this->getPos().getX() != this->_startPos.getX()) this->_pos.setX(this->_startPos.getX());
	if (this->getPos().getY() < this->_startPos.getY() - 7) this->_pos.setY(this->_startPos.getY());
	else if (this->getPos().getY() > this->_startPos.getY()) this->_pos.setY(this->_startPos.getY() - 7);
}

std::ostream	&operator<<(std::ostream &o, GamePiece const &i) {
	return o << "Game Piece Info:" << std::endl <<
	"pos: " << i.getPos() << std::endl <<
	"sprite: " << i.getSprite() << std::endl <<
	"input: " << i.getStartPos() << std::endl;
}
