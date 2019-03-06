#ifndef GAME_STATE_CLASS_HPP
	#define GAME_STATE_CLASS_HPP

	#include "Vector2D.class.hpp"

	// To keep track of the state of the game
	enum							State {
									LOADING,
									STARTING,
									PLAYING,
									PAUSE,
									GAMEOVER,
									EXITING
	};

	class GameState {

		// Storing window demensions
		Vector2D<uint_fast32_t> 	_winDem;
		// Storing the cur state of the game
		State						_curState;
		// Storing all actors
		//Actor						*_actors[AMOUNT_OF_PLAYERS + 2];

	public:
		// Constructors --
		GameState(Vector2D<uint_fast32_t> winDem);
		GameState(GameState const &src);
		~GameState(void);

		// Overload operators --
		GameState					&operator=(GameState const &rhs);

		// Getters --
		Vector2D<uint_fast32_t>		getWinDem(void) const;
		State						getCurState(void) const;

		// Setters --
		void						setWinDem(Vector2D<uint_fast32_t> winDem);
		State						setCurState(State curState);

		// Helper methods
		bool						bShouldExit(void);
		void						runMainLoop(void);
		void						runWinUpdate(bool bIsToSmall);
		void                        handleInput(int input);

		// Run the state
		bool						runState(void);

	private:
		void                        _draw(void);

		// Private Constructors --
		//void						_initAllActors(void);

		// Private De-constructors --
		//void						_deleteAllActors(void);

		// Private setters --
		//void						_setAllActorsCanDraw(bool bCanDraw);

		// Private helper methods --
		void						_startMainGame(void);
		void						_handleMainGame(void);
		void						_handleGameOver(void);
		//void 						_tickAllActors(void);
		void						_mainWindowRedraw(void);
		void						_gameOverWindowRedraw(void);

	};

	// To print the game state info
	std::ostream      		&operator<<(std::ostream &o, GameState const &i);

#endif
