#ifndef GAME_STATE_HANDLER_CLASS_HPP
	#define GAME_STATE_HANDLER_CLASS_HPP

	#include <includes.hpp>

	// Forward declaring classes
	template<typename T> class			Vector2D;
	class								GameState;

	// State enum to keep track of the state of the game
	enum								State {
										LOADING,
										STARTING,
										PLAYING,
										TESTING,
										GAMEOVER,
										ERROR,
										EXITING
	};

	class GameStateHandler {

		// Storing window dimensions
		Vector2D<uint_fast32_t> 		_winDem;
		// Storing the cur state of the game
		State							_curState;
		// Storing current GameState
		GameState*						_gameState;

	public:
		// Constructors --
		GameStateHandler(Vector2D<uint_fast32_t> const winDem);
		GameStateHandler(GameStateHandler const &src);
		~GameStateHandler(void);

		// Overload operators --
		GameStateHandler				&operator=(GameStateHandler const &rhs);

		// Getters --
		Vector2D<uint_fast32_t> const	getWinDem(void) const;
		State							getCurState(void) const;
		GameState*						getGameState(void) const;

		// Setters --
		void							setWinDem(Vector2D<uint_fast32_t> winDem);
		State							setCurState(State curState);
		void							setGameState(GameState *gameState);

		// Public helper methods --
		void                        	handleInput(int input);
		bool							runState(void);

	private:
		// Private helper methods --
		void							_chooseGameState(void);
		bool							_checkStateChange(void);
		bool							_checkWinDimChange(void);
		void                        	_draw(void);
		void							_handleLoadingState(void);

		// Private free methods --
		void							_deleteGameState(void);

	};

	// To print the game state info
	std::ostream      					&operator<<(std::ostream &o, GameStateHandler const &i);

#endif
