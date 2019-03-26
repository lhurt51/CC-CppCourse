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
		static Vector2D<uint_fast32_t> 		_winDem;
		// Storing the cur state of the game
		static State						_curState;
		// Storing current GameState
		static GameState*					_gameState;

	public:

		// Getters --
		static Vector2D<uint_fast32_t>	getWinDim(void);
		static State					getCurState(void);
		static GameState*				getGameState(void);

		// Setters --
		static void						setWinDim(Vector2D<uint_fast32_t> winDem);
		static State					setCurState(State curState);
		static void						setGameState(GameState *gameState);

		// Public helper methods --
		static void                     handleInput(int input);
		static bool						runState(void);

	private:
		// Private helper methods --
		static void						_chooseGameState(void);
		static bool						_checkStateChange(void);
		static bool						_checkWinDimChange(void);
		static void                     _draw(bool stateChange);
		static void						_handleLoadingState(void);

		// Private free methods --
		static void						_deleteGameState(void);

	};

	// To print the game state info
	std::ostream      					&operator<<(std::ostream &o, GameStateHandler const &i);

#endif
