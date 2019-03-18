#ifndef GAME_STATE_CLASS_HPP
	#define GAME_STATE_CLASS_HPP

	#include <includes.hpp>

	// Forward declaring classes
	template<typename T> class			Vector2D;

	/********************************\
	 * WANT TO ADD GAME STATE		*
	 * HANDLER THAT USES THE GAME	*
	 * ENGINE TO UPDATE A GAME		*
	 * STATE POINTER TO A NEW		*
	 * GAME STATE BASED ON STATE	*
	\********************************/

	class GameState {

		// Storing window dimensions
		Vector2D<uint_fast32_t>& 		_winDem;

	public:
		// Constructors --
		GameState(Vector2D<uint_fast32_t>& winDem);
		GameState(GameState const &src);
		~GameState(void);

		// Overload operators --
		GameState						&operator=(GameState const &rhs);

		// Getters --
		Vector2D<uint_fast32_t>&		getWinDem(void) const;

		// Helper methods abstract methods
		virtual void                    handleInput(int input) = 0;
		virtual void					hanldeTick(void) = 0;

	private:
		// Private helper methods --

		// Private Initializers

		// Private Delete --
	};

	// To print the game state info
	std::ostream      					&operator<<(std::ostream &o, GameState const &i);

#endif
