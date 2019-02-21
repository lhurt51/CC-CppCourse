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

#include "GameState.class.hpp"
#include "Game.class.hpp"

GameState::GameState(void) : _winDem(Vector2D(0)), _curState(LOADING) {
	setBoard(Vector2D(-1));
	return;
}

GameState::GameState(Vector2D winDem) : _winDem(winDem), _curState(LOADING) {
	return;
}

GameState::GameState(GameState const &src) {
	*this = src;
	return;
}

GameState::~GameState(void) {
	_deleteBoard();
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

void				GameState::setBoard(Vector2D pos) {
	if (pos >= Vector2D(0))
		this->_board = new Board(pos);
	else
		this->_board = new Board();
}

void				GameState::setPlayers(Board *board) {
	char randomChar[] = "abcdefghijklmnopqrstuvwxyz";

	if (board == NULL) return;
	this->_players.reserve(AMOUNT_OF_PLAYERS);
	for (int i = 0; i < AMOUNT_OF_PLAYERS; i++) {
		char const randC = randomChar[(rand() % strlen(randomChar))];
		this->_players.push_back(Player(board, randC));
	}
}

void				GameState::setGamePiece(Player *player) {
	if (player == NULL) return;
	this->_gamePiece = new GamePiece(player->getBoard(), player->getSprite(), player->getPos());
}

void				GameState::initAllActors(void) {
	for (unsigned int i = 0; i < sizeof(_actors) / sizeof(*_actors); i++)
		_actors[i] = NULL;
	setBoard(Vector2D(HALF_OF_VAL(_winDem.getX()), HALF_OF_VAL(_winDem.getY())));
	_actors[0] = this->_board;
	setPlayers(this->_board);
	for (unsigned int i = 1; i < AMOUNT_OF_PLAYERS + 1; i++)
		_actors[i] = &this->_players[i - 1];
}

void				GameState::deleteAllActors(void) {
	for (unsigned int i = 0; i < sizeof(_actors) / sizeof(*_actors); i++) {
		delete _actors[i];
		_actors[i] = NULL;
	}
}

void				GameState::runMainLoop(void) {

}

void				GameState::runWinUpdate(bool bIsToSmall) {
	char msg[] = "Error! Window too small";

	clear();
	if (bIsToSmall) {
		// board.setCanDraw(false);
		// player1.setCanDraw(false);
		mvprintw(HALF_OF_VAL(_winDem.getY()), HALF_OF_VAL(_winDem.getX()) - HALF_OF_VAL(strlen(msg)),"%s",msg);
	} else {
		// board.setCanDraw(true);
		// player1.setCanDraw(true);
		// board.setPos(Vector2D(HALF_OF_VAL(_winDem.getX()), HALF_OF_VAL(this->_winDem.getY())));
		// player1.shouldUpdate();
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
