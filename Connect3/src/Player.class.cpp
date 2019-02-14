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

#include <ncurses.h>
#include "Actor.class.hpp"
#include "Player.class.hpp"

static int		conID = 0;

Vector2D		Player::_spawnLoc = Vector2D();

Player::Player(WINDOW *window, char const sprite) : Actor(Vector2D(0), sprite), _id(conID++), _window(window), _bExitReq(false) {
	return;
}

Player::Player(Player const &src) : Actor(src) {
	*this = src;
	return;
}

Player::~Player(void) {
	return;
}

Player			&Player::operator=(Player const &rhs) {
	if (this != &rhs) {
		this->_pos = rhs.getPos();
		this->_input = rhs.getUserInput();
		this->_bExitReq = rhs.getExitReq();
	}
	return *this;
}

int					Player::getPlayerID(void) const {
	return this->_id;
}

int					Player::getUserInput(void) const {
	return this->_input;
}

bool				Player::getExitReq(void) const {
	return this->_bExitReq;
}

bool				Player::setSpawnLoc(Vector2D spawnLoc) {
	if (Player::_spawnLoc == spawnLoc) return false;
	Player::_spawnLoc = spawnLoc;
	return true;
}

void				Player::tick(void) {
	this->_input = wgetch(this->_window);
	if (!this->_checkInput()) return;
	this->clear();
	this->_handleUserInput();
	this->_checkPos();
	this->draw();
}

void 				Player::_checkPos(void) {
	if (this->getPos().getY() != 0) this->getPos().setY(0);
	if (this->getPos().getX() > 5) this->getPos().setX(0);
	else if (this->getPos().getX() < 0) this->getPos().setX(5);

}

bool 				Player::_checkInput(void) {
	switch (this->_input) {
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

void				Player::_handleUserInput(void) {
	switch(this->_input) {
		case 'q':
			this->_bExitReq = true;
			break;
		case KEY_LEFT:
		case 'a':
			this->move(Vector2D(-1, 0));
			break;
		case KEY_RIGHT:
		case 'd':
			this->move(Vector2D(1, 0));
		default:
			break;
	}
}

std::ostream	&operator<<(std::ostream &o, Player const &i) {
	return o << "Player Info:" << std::endl <<
	"pos: " << i.getPos() << std::endl <<
	"sprite: " << i.getSprite() << std::endl <<
	"input: " << i.getUserInput() << std::endl <<
	"exit req: " << i.getExitReq() << std::endl;
}
