#ifndef EMPTY_GAME_MENU_ITEM_CLASS_HPP
	#define EMPTY_GAME_MENU_ITEM_CLASS_HPP

	#include <includes.hpp>
	#include "MenuItem.class.hpp"

	class 					GameState;

	class EmptyGameMenuItem : public MenuItem {

		// Reference to game state to change the state
		GameState&			_gameState;

	public:
		// Constructors --
		EmptyGameMenuItem(GameState &gameState, Vector2D<uint_fast32_t> const pos, std::string const &sprite);
		EmptyGameMenuItem(EmptyGameMenuItem const &src);
		~EmptyGameMenuItem(void);

		// Overload operators --
		EmptyGameMenuItem	&operator=(EmptyGameMenuItem const &rhs);

		// Getters --
		GameState			&getGameState(void) const;

	protected:

		// Override Menu Item execute code
		void				_execute(void);

	};

	// To print the game state info
	std::ostream      	&operator<<(std::ostream &o, EmptyGameMenuItem const &i);

#endif
