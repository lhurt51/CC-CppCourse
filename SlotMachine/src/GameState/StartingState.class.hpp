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
		virtual void					handleResize(void) override;
		virtual void                    handleInput(int input) override;
		virtual void					handleTick(void) override;

	};

	// To print the game state info --
	std::ostream      					&operator<<(std::ostream &o, StartingState const &i);

#endif
