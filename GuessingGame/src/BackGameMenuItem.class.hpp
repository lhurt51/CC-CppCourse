#ifndef BACK_GAME_MENU_ITEM_CLASS_HPP
	#define BACK_GAME_MENU_ITEM_CLASS_HPP

	#include <includes.hpp>
	#include "MenuItem.class.hpp"

	class 					GameState;

	class BackGameMenuItem : public MenuItem {

		// Reference to game state to change the state
		GameState&			_gameState;

	public:
		// Constructors --
		BackGameMenuItem(GameState &gameState, Vector2D<uint_fast32_t> const pos, std::string const &sprite);
		BackGameMenuItem(BackGameMenuItem const &src);
		~BackGameMenuItem(void);

		// Overload operators --
		BackGameMenuItem	&operator=(BackGameMenuItem const &rhs);

		// Getters --
		GameState			&getGameState(void) const;

	protected:

		// Override Menu Item execute code
		void				_execute(void);

	};

	// To print the game state info
	std::ostream      	&operator<<(std::ostream &o, BackGameMenuItem const &i);

#endif
