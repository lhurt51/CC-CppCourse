#ifndef STARTING_STATE_CLASS_HPP
	#define STARTING_STATE_CLASS_HPP

	#include "GameState.class.hpp"

	class StartingState : public GameState {

	public:

		// Constructors --
		StartingState(void);
		StartingState(StartingState const &src);
		virtual ~StartingState(void);

		// Overload operators --
		StartingState					&operator=(StartingState const &rhs);

		// Getters --

		// Helper methods abstract methods --
		virtual void					handleResize(void);
		virtual void					hideAllGameObjects(void);
		virtual void					showAllGameObjects(void);
		virtual void					printAllGameObjects(void);
		virtual bool					checkForActorUpdate(void);
		virtual void                    handleInput(int input);
		virtual void					handleTick(void);

	};

	// To print the game state info --
	std::ostream      					&operator<<(std::ostream &o, StartingState const &i);

#endif
