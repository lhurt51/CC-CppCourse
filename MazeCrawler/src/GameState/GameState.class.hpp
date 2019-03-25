#ifndef GAME_STATE_CLASS_HPP
	#define GAME_STATE_CLASS_HPP

	#include <includes.hpp>

	class GameState {

	public:

		// Constructors --
		GameState(void);
		GameState(GameState const &src);
		virtual ~GameState(void);

		// Overload operators --
		GameState						&operator=(GameState const &rhs);

		// Helper methods abstract methods --
		virtual void					handleResize(void) = 0;
		virtual void					hideAllGameObjects(void) = 0;
		virtual void					showAllGameObjects(void) = 0;
		virtual void					printAllGameObjects(void) = 0;
		virtual bool					checkForActorUpdate(void) = 0;
		virtual void                    handleInput(int input) = 0;
		virtual void					handleTick(void) = 0;

	};

	// To print the game state info --
	std::ostream      					&operator<<(std::ostream &o, GameState const &i);

#endif
