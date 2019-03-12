#ifndef GAME_STATE_CLASS_HPP
	#define GAME_STATE_CLASS_HPP

	#include <includes.hpp>

	// Forward declaring classes
	template<typename T> class			Vector2D;
	class								Player;
	class								MenuHandler;

	// To keep track of the state of the game
	enum								State {
										LOADING,
										STARTING,
										PLAYING,
										GAMEOVER,
										ERROR,
										EXITING
	};

	class GameState {

		// Storing window dimensions
		Vector2D<uint_fast32_t> 		_winDem;
		// Storing the cur state of the game
		State							_curState;
		// Storing a pointer to the player
		Player							*_player;
		// Storing a pointer to a menu handler
		MenuHandler						*_menuHandler;

	public:
		// Constructors --
		GameState(Vector2D<uint_fast32_t> const winDem);
		GameState(GameState const &src);
		~GameState(void);

		// Overload operators --
		GameState						&operator=(GameState const &rhs);

		// Getters --
		Vector2D<uint_fast32_t> const	getWinDem(void) const;
		State							getCurState(void) const;

		// Setters --
		void							setWinDem(Vector2D<uint_fast32_t> const winDem);
		State							setCurState(State curState);

		// Helper methods
		void                        	handleInput(int input);

		// Run the state
		bool							runState(void);

	private:
		// Private helper methods --
		void                        	_draw(void);
		void							_handleLoadingState(void);
		void							_handleStartingState(void);
		void							_handlePlayingState(void);
		void 							_handleGameOverState(void);
		void 							_handleErrorState(void);
		void							_handleExitingState(void);

		// Private Initializers

		// Private Delete --
		void							_deletePlayer(void);
		void							_deleteMenuHandler(void);

	};

	// To print the game state info
	std::ostream      					&operator<<(std::ostream &o, GameState const &i);

#endif
