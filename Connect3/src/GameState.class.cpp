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

#include <time.h>
#include "GameState.class.hpp"
#include "Game.class.hpp"

GameState::GameState(Vector2D winDem) : _winDem(winDem), _curState(LOADING), _curPlayer(0) {
	initAllActors();
	return;
}

GameState::GameState(GameState const &src) {
	*this = src;
	return;
}

GameState::~GameState(void) {
	deleteAllActors();
	return;
}

GameState			&GameState::operator=(GameState const &rhs) {
	if (this != &rhs) {
		this->_winDem = rhs.getWinDem();
		this->_curState = rhs.getCurState();
		this->_board = rhs.getBoard();
	}
	return *this;
}

Vector2D			GameState::getWinDem(void) const {
	return this->_winDem;
}

State				GameState::getCurState(void) const {
	return this->_curState;
}

int					GameState::getCurPlayer(void) const {
	return this->_curPlayer;
}

Board				*GameState::getBoard(void) const {
	return this->_board;
}

std::vector<Player>	GameState::getPlayers(void) const {
	return this->_players;
}

GamePiece			*GameState::getGamePiece(void) const {
	return this->_gamePiece;
}

void				GameState::setWinDem(Vector2D winDem) {
	if (this->_winDem == winDem) return;
	this->_winDem = winDem;
}

void				GameState::setCurState(State curState) {
	if (this->_curState == curState) return;
	this->_curState = curState;
}

void					GameState::setCurPlayer(int player) {
	if (_curPlayer != player) _curPlayer = player;
	for (unsigned int i = 0; i < _players.size(); i++) {
		if (_curPlayer == (int)i)
			_players[i].setIsTurn(true);
		else
			_players[i].setIsTurn(false);
		_players[i].shouldUpdate();
	}
}

void				GameState::setBoard(Vector2D pos) {
	if (pos >= Vector2D(0))
		this->_board = new Board(pos);
	else
		this->_board = new Board();
}

void				GameState::setPlayers(Board *board) {
	char randomChar[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

	if (board == nullptr) return;
	// initialize random seed
  	srand (time(NULL));
	// Reserve space for the players
	this->_players.reserve(AMOUNT_OF_PLAYERS);
	for (unsigned int i = 0; i < AMOUNT_OF_PLAYERS; i++) {
		char const randC = randomChar[(std::rand() % (strlen(randomChar) - 1))];
		this->_players.push_back(Player(board, randC));
	}
}

void				GameState::setGamePiece(Player *player) {
	if (player == nullptr) return;
	this->_gamePiece = player->createPiece();
}

bool				GameState::bShouldExit(void) {
	for (unsigned int i = 0; i < _players.size(); i++) {
		if (_players[i].getExitReq())
			return true;
	}
	return false;
}

void				GameState::initAllActors(void) {
	for (unsigned int i = 0; i < sizeof(_actors) / sizeof(*_actors); i++)
		_actors[i] = nullptr;
	setBoard(Vector2D(HALF_OF_VAL(_winDem.getX()), HALF_OF_VAL(_winDem.getY())));
	_actors[0] = this->_board;
	setPlayers(this->_board);
	for (unsigned int i = 1; i < AMOUNT_OF_PLAYERS + 1; i++)
		_actors[i] = &this->_players[i - 1];
}

void				GameState::deleteAllActors(void) {
	for (unsigned int i = 0; i < sizeof(_actors) / sizeof(*_actors); i++)
		_actors[i] = nullptr;
	_deleteBoard();
	_deletePlayers();
	_deleteGamePiece();
}

void				GameState::setAllActorsCanDraw(bool bCanDraw) {
	for (unsigned int i = 0; i < sizeof(_actors) / sizeof(*_actors); i++) {
		if (_actors[i]) _actors[i]->setCanDraw(bCanDraw);
	}
}

void 				GameState::tickAllActors(void) {
	for (unsigned int i = 0; i < sizeof(_actors) / sizeof(*_actors); i++) {
		if (_actors[i]) _actors[i]->tick();
	}
}

void				GameState::checkGamePiece(void) {
	if (_gamePiece == nullptr)
		_gamePiece = _players[_curPlayer].createPiece();
	else {
		if (_gamePiece->getCanClear()) {
			_actors[4] = nullptr;
			delete _gamePiece;
			_gamePiece = nullptr;
		} else if (_actors[4] == nullptr) {
			_actors[4] = _gamePiece;
			_actors[4]->setCanDraw(true);
		}
	}
}

void				GameState::runMainLoop(void) {
	tickAllActors();
	checkGamePiece();
}

void				GameState::runWinUpdate(bool bIsToSmall) {
	char msg[] = "Error! Window too small";

	clear();
	if (bIsToSmall) {
		setAllActorsCanDraw(false);
		mvprintw(HALF_OF_VAL(_winDem.getY()), HALF_OF_VAL(_winDem.getX()) - HALF_OF_VAL(strlen(msg)),"%s",msg);
	} else {
		setAllActorsCanDraw(true);
		_board->setPos(Vector2D(HALF_OF_VAL(_winDem.getX()), HALF_OF_VAL(_winDem.getY())));
		setCurPlayer(1);
		_players[_curPlayer].shouldUpdate();
		mvprintw(_winDem.getY() - 5, 5, "Width: %d and Height: %d", _winDem.getX(), _winDem.getY());
	}
	wborder(Game::getWindow(), '|', '|', '-', '-', 'o', 'o', 'o', 'o');
}

void				GameState::_deleteBoard(void) {
	delete this->_board;
}

void				GameState::_deletePlayers(void) {
	this->_players.clear();
}

void				GameState::_deleteGamePiece(void) {
	delete this->_gamePiece;
}

std::ostream		&operator<<(std::ostream &o, GameState const &i) {
	return o << "Game State Info:" << std::endl <<
	"window demensions: " << i.getWinDem() << std::endl <<
	"state: " << i.getCurState() << std::endl <<
	"board: " << i.getBoard() << std::endl;
}
