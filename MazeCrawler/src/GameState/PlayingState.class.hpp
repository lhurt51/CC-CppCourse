#ifndef PLAYING_STATE_CLASS_HPP
	#define PLAYING_STATE_CLASS_HPP

	#include "GameState.class.hpp"

	class PlayingState : public GameState {

	public:

		// Constructors --
		PlayingState(void);
		PlayingState(PlayingState const &src);
		virtual ~PlayingState(void);

		// Overload operators --
		PlayingState					&operator=(PlayingState const &rhs);

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
	std::ostream      					&operator<<(std::ostream &o, PlayingState const &i);

#endif
