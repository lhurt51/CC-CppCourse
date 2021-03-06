#ifndef GAME_STATE_CLASS_HPP
	#define GAME_STATE_CLASS_HPP

	#include <vector>
	#include "Board.class.hpp"
	#include "Player.class.hpp"
	#include "GamePiece.class.hpp"

	// To keep track of the state of the game
	enum					State {
							LOADING,
							PLAYING,
							GAMEOVER
	};

	class GameState {

		// Storing window demensions
		Vector2D 			_winDem;
		// Storing the cur state of the game
		State				_curState;
		// Storing the int of the cur player
		int					_curPlayer;
		// Storing all actors, total is 5 (1 for the board) (1 for a gamepiece) (3 for players)
		Actor				*_actors[AMOUNT_OF_PLAYERS + 2];
		// A pointer to the board being stored in memory
		Board				*_board;
		// An array of players
		std::vector<Player>	_players;
		// A pointer to the game piece that might be stored
		GamePiece			*_gamePiece;

	public:
		// Constructors --
		GameState(Vector2D winDem);
		GameState(GameState const &src);
		~GameState(void);

		// Overload operators --
		GameState			&operator=(GameState const &rhs);

		// Getters --
		Vector2D			getWinDem(void) const;
		State				getCurState(void) const;
		int					getCurPlayer(void) const;
		Board				*getBoard(void) const;
		std::vector<Player>	getPlayers(void) const;
		GamePiece			*getGamePiece(void) const;

		// Setters --
		void				setWinDem(Vector2D winDem);
		void				setCurState(State curState);
		void				setCurPlayer(int player);
		void				setBoard(Vector2D pos);
		void				setPlayers(Board *board);
		void				setGamePiece(Player *player);


		// Helper methods
		bool				bShouldExit(void);
		void				runMainLoop(void);
		void				runWinUpdate(Vector2D winDem, bool bIsToSmall);

	private:

		// Private Constructors --
		void				_initAllActors(void);

		// Private De-constructors --
		void				_deleteAllActors(void);
		void				_deleteBoard(void);
		void				_deletePlayers(void);
		void				_deleteGamePiece(void);

		// Private setters --
		void				_setAllActorsCanDraw(bool bCanDraw);

		// Private helper methods --
		void				_checkGamePiece(void);
		void				_handleGameOver(void);
		void 				_tickAllActors(void);
		void				_mainWindowRedraw(void);
		void				_gameOverWindowRedraw(void);

	};

	// To print the game state info
	std::ostream      		&operator<<(std::ostream &o, GameState const &i);

#endif
