#ifndef GAME_STATE_CLASS_HPP
	#define GAME_STATE_CLASS_HPP

	#include <vector>
	#include "Board.class.hpp"
	#include "Player.class.hpp"
	#include "GamePiece.class.hpp"

	enum					State {
							LOADING,
							PLAYING,
							GAMEOVER
	};

	class GameState {

		Vector2D 			_winDem;
		State				_curState;
		int					_curPlayer;
		Actor				*_actors[AMOUNT_OF_PLAYERS + 2];
		Board				*_board;
		std::vector<Player>	_players;
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
		void				initAllActors(void);
		void				deleteAllActors(void);
		void				setAllActorsCanDraw(bool bCanDraw);
		void 				tickAllActors(void);
		void				checkGamePiece(void);
		void				runMainLoop(void);
		void				runWinUpdate(bool bIsToSmall);

	private:

		// De-constructors --
		void				_deleteBoard(void);
		void				_deletePlayers(void);
		void				_deleteGamePiece(void);

	};

	// To print the game state info
	std::ostream      		&operator<<(std::ostream &o, GameState const &i);

#endif
