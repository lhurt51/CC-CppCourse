#ifndef GAME_STATE_CLASS_HPP
	#define GAME_STATE_CLASS_HPP

	#include <includes.hpp>

	// Forward declaring classes
	template<typename T> class			Vector2D;

	class GameState {

		// Storing window dimensions
		Vector2D<uint_fast32_t>& 		_winDim;

	public:

		// Constructors --
		GameState(Vector2D<uint_fast32_t>& winDim);
		GameState(GameState const &src);
		virtual ~GameState(void);

		// Overload operators --
		GameState						&operator=(GameState const &rhs);

		// Getters --
		Vector2D<uint_fast32_t>&		getWinDim(void) const;

		// Helper methods abstract methods --
		virtual void					hideAllGameObjects(void) = 0;
		virtual void					showAllGameObjects(void) = 0;
		virtual bool					printAllGameObjects(void) = 0;
		virtual bool					checkForActorUpdate(void) = 0;
		virtual void                    handleInput(int input) = 0;
		virtual void					handleTick(void) = 0;

	};

	// To print the game state info --
	std::ostream      					&operator<<(std::ostream &o, GameState const &i);

#endif
