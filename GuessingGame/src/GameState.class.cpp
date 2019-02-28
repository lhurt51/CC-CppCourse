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

// Initializer for windem Constructor
GameState::GameState(Vector2D winDem) : _winDem(winDem), _curState(LOADING), _curPlayer(0) {
	_initAllActors();
	return;
}

// Copy constructor
GameState::GameState(GameState const &src) {
	*this = src;
	return;
}

// Deconstructor
GameState::~GameState(void) {
	_deleteAllActors();
	return;
}

// Equal sign overload for the copy constructor
GameState			&GameState::operator=(GameState const &rhs) {
	if (this != &rhs) {
		this->_winDem = rhs.getWinDem();
		this->_curState = rhs.getCurState();
		this->_curPlayer = rhs.getCurPlayer();
		this->_board = rhs.getBoard();
		this->_players = rhs.getPlayers();
		this->_gamePiece = rhs.getGamePiece();
	}
	return *this;
}

// Game State Getters --
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
// Game State Getters --

// Game State Setters --
void				GameState::setWinDem(Vector2D winDem) {
	if (this->_winDem == winDem) return;
	this->_winDem = winDem;
}

void				GameState::setCurState(State curState) {
	if (this->_curState == curState) return;
	this->_curState = curState;
}

void					GameState::setCurPlayer(int player) {
	if (_curPlayer != player)
		_curPlayer = player;
	if (_curPlayer > AMOUNT_OF_PLAYERS - 1 || _curPlayer < 0)
		_curPlayer = 0;
	for (unsigned int i = 0; i < _players.size(); i++) {
		if (_curPlayer == (int)i)
			_players[i].setIsTurn(true);
		else
			_players[i].setIsTurn(false);
		_players[i].shouldUpdate();
	}
	mvprintw(_winDem.getY() - 7, HALF_OF_VAL(_winDem.getX()) - HALF_OF_VAL(strlen("Current Player - Player #%d")), "Current Player - Player #%d", _curPlayer + 1);
}

void				GameState::setBoard(Vector2D pos) {
	if (pos >= Vector2D(0))
		this->_board = new Board(pos);
	else
		this->_board = new Board();
}

void				GameState::setPlayers(Board *board) {
	char randomChar[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	// char usedSprites[AMOUNT_OF_PLAYERS];

	if (board == nullptr) return;
	// initialize random seed
  	srand (time(NULL));
	// Reserve space for the players
	this->_players.reserve(AMOUNT_OF_PLAYERS);
	for (unsigned int i = 0; i < AMOUNT_OF_PLAYERS; i++) {
		// Need to fix rand finding two identical sprites !!!!!!
		char const randC = randomChar[(std::rand() % (strlen(randomChar) - 1))];
		this->_players.push_back(Player(board, randC));
	}
}

void				GameState::setGamePiece(Player *player) {
	if (player == nullptr) return;
	this->_gamePiece = player->createPiece();
}
// Game State Setters --

// Check for exit request a request break from program
bool				GameState::bShouldExit(void) {
	for (unsigned int i = 0; i < _players.size(); i++) {
		if (_players[i].getExitReq())
			return true;
	}
	return false;
}

// Run the main game loop base on the current state
void				GameState::runMainLoop(void) {
	switch (_curState) {
		case LOADING:
			_curState = PLAYING;
		case PLAYING:
			_tickAllActors();
			_checkGamePiece();
			break;
		case GAMEOVER:
			_handleGameOver();
			break;
		default:
			break;
	}
}

// Run a window update checking for a too small screen otherwise based off of current state
void				GameState::runWinUpdate(Vector2D winDem, bool bIsToSmall) {
	char title[] = "Connect 3";
	char error[] = "Window too small";

	clear();
	setWinDem(winDem);
	if (bIsToSmall) {
		_setAllActorsCanDraw(false);
		mvprintw(HALF_OF_VAL(_winDem.getY()), HALF_OF_VAL(_winDem.getX()) - HALF_OF_VAL(strlen(error)), error);
	} else {
		switch(_curState) {
			case LOADING:
				_curState = PLAYING;
			case PLAYING:
				_mainWindowRedraw();
				break;
			case GAMEOVER:
				_gameOverWindowRedraw();
				break;
			default:
				break;
		}
		mvprintw(3, HALF_OF_VAL(_winDem.getX()) - HALF_OF_VAL(strlen(title)), title);
	}
	wborder(Game::getWindow(), '|', '|', '-', '-', 'o', 'o', 'o', 'o');
}

// Initialize all pointer attributes
void				GameState::_initAllActors(void) {
	// Initialize a list of actors to nullptr
	for (unsigned int i = 0; i < sizeof(_actors) / sizeof(*_actors); i++)
		_actors[i] = nullptr;
	// Setting the board using a custom method and a custom position
	setBoard(Vector2D(HALF_OF_VAL(_winDem.getX()) + HALF_OF_VAL(BOARD_COLUMN), HALF_OF_VAL(_winDem.getY()) + HALF_OF_VAL(BOARD_ROW)));
	// Setting the board as the first actor
	_actors[0] = this->_board;
	// Initialize the players using the board
	setPlayers(this->_board);
	// Assign the players to the actor array leaving one space for a game piece
	for (unsigned int i = 1; i < AMOUNT_OF_PLAYERS + 1; i++)
		_actors[i] = &this->_players[i - 1];
}

// Delete all pointer attributes
void				GameState::_deleteAllActors(void) {
	for (unsigned int i = 0; i < sizeof(_actors) / sizeof(*_actors); i++)
		_actors[i] = nullptr;
	_deleteBoard();
	_deletePlayers();
	_deleteGamePiece();
}

// Delete the board if the Board is not null
void				GameState::_deleteBoard(void) {
	if (this->_board != nullptr) {
		delete this->_board;
		this->_board = nullptr;
	}
}

// Delete the players if the players array is not empty
void				GameState::_deletePlayers(void) {
	if (!this->_players.empty()) this->_players.clear();
}

// Delete the game piece if it exists
void				GameState::_deleteGamePiece(void) {
	if (this->_gamePiece != nullptr) {
		delete this->_gamePiece;
		this->_gamePiece = nullptr;
	}
}

// Set all actors can draw to the input param
void				GameState::_setAllActorsCanDraw(bool bCanDraw) {
	for (unsigned int i = 0; i < sizeof(_actors) / sizeof(*_actors); i++) {
		if (_actors[i]) _actors[i]->setCanDraw(bCanDraw);
	}
}

// Check if there is a game piece and if it is placed check for win game state
void				GameState::_checkGamePiece(void) {
	if (_gamePiece == nullptr) {
		_gamePiece = _players[_curPlayer].createPiece();
		if (_gamePiece != nullptr && _actors[4] == nullptr) {
			_actors[4] = _gamePiece;
			_actors[4]->setCanDraw(true);
		}
	} else {
		if (_gamePiece->getCanClear()) {
			if (_gamePiece->getFoundPos()) {
				if (_board->getHasWon())
					setCurState(GAMEOVER);
				else
					setCurPlayer(_curPlayer + 1);
			}
			_actors[4] = nullptr;
			_deleteGamePiece();
		}
	}
}

// Handle game over state for main loop
void				GameState::_handleGameOver(void) {
	static int i = 0;

	if (i == 0) {
		runWinUpdate(_winDem, false);
		i++;
	}
	_tickAllActors();
}

// Tick all actors in the actors list
void 				GameState::_tickAllActors(void) {
	for (unsigned int i = 0; i < sizeof(_actors) / sizeof(*_actors); i++) {
		if (_actors[i]) _actors[i]->tick();
	}
}

// The Main window redraw for loading and playing game states
void				GameState::_mainWindowRedraw(void) {
	_setAllActorsCanDraw(true);
	_board->setPos(Vector2D(HALF_OF_VAL(_winDem.getX()) + HALF_OF_VAL(BOARD_COLUMN), HALF_OF_VAL(_winDem.getY()) + HALF_OF_VAL(BOARD_ROW)));
	setCurPlayer(_curPlayer);
}

// Game over window redraw for when the game is over
void				GameState::_gameOverWindowRedraw(void) {
	_setAllActorsCanDraw(false);
	mvprintw(HALF_OF_VAL(_winDem.getY()), HALF_OF_VAL(_winDem.getX()) - HALF_OF_VAL(strlen("Game Over!")), "Game Over!");
	mvprintw(HALF_OF_VAL(_winDem.getY()) + 1, HALF_OF_VAL(_winDem.getX()) - HALF_OF_VAL(strlen("Player #%d has won!")), "Player #%d has won!", _curPlayer + 1);
}

// Out stream overload for testing
std::ostream		&operator<<(std::ostream &o, GameState const &i) {
	return o << "Game State Info:" << std::endl <<
	"window demensions: " << i.getWinDem() << std::endl <<
	"state: " << i.getCurState() << std::endl <<
	"board: " << i.getBoard() << std::endl;
}
