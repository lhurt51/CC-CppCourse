#ifndef GAME_STATE_CLASS_HPP
	#define GAME_STATE_CLASS_HPP

	#include <includes.hpp>

	template<typename T>
    class Vector2D;

	class Player;

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
		// Storing a pointer to the player
		Player						*_player;

	public:
		// Constructors --
		GameState(Vector2D<uint_fast32_t> const winDem);
		GameState(GameState const &src);
		~GameState(void);

		// Overload operators --
		GameState					&operator=(GameState const &rhs);

		// Getters --
		Vector2D<uint_fast32_t> const	getWinDem(void) const;
		State						getCurState(void) const;

		// Setters --
		void						setWinDem(Vector2D<uint_fast32_t> const winDem);
		State						setCurState(State curState);

		// Helper methods
		bool						bShouldExit(void);
		void						runMainLoop(void);
		void						runWinUpdate(bool const bIsToSmall);
		void                        handleInput(int input);

		// Run the state
		bool						runState(void);

	private:
		void                        _draw(void);

		// Private helper methods --
		void						_startMainGame(void);
		void						_handleMainGame(void);
		void						_handleGameOver(void);
		void						_mainWindowRedraw(void);
		void						_gameOverWindowRedraw(void);

	};

	// To print the game state info
	std::ostream      		&operator<<(std::ostream &o, GameState const &i);

#endif
