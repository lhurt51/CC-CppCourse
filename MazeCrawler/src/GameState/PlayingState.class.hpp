#ifndef PLAYING_STATE_CLASS_HPP
	#define PLAYING_STATE_CLASS_HPP

	#include "GameState.class.hpp"

	// Forward declaring classes
	class								Maze;

	class PlayingState : public GameState {

		Maze*							_maze;

	public:

		// Constructors --
		PlayingState(void);
		PlayingState(PlayingState const &src);
		virtual ~PlayingState(void);

		// Overload operators --
		PlayingState					&operator=(PlayingState const &rhs);

		// Getters --

		// Helper methods abstract methods --
		virtual void					handleResize(void) override;
		virtual void                    handleInput(int input) override;
		virtual void					handleTick(void) override;

	};

	// To print the game state info --
	std::ostream      					&operator<<(std::ostream &o, PlayingState const &i);

#endif
