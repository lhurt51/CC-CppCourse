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

		// Game state base helper methods --
		void							hideAllGameObjects(void);
		void							showAllGameObjects(void);
		void							printAllGameObjects(void);
		bool							checkForActorUpdate(void);

		// To implement logic onttop
		virtual void					handleTick(void);

		// Helper methods abstract methods --
		virtual void					handleResize(void) = 0;
		virtual void                    handleInput(int input) = 0;

	};

	// To print the game state info --
	std::ostream      					&operator<<(std::ostream &o, GameState const &i);

#endif
