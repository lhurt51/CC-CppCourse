#ifndef EXIT_GAME_MENU_ITEM_CLASS_HPP
	#define EXIT_GAME_MENU_ITEM_CLASS_HPP

	#include <includes.hpp>
	#include "MenuItem.class.hpp"

	class 					GameState;

	class ExitGameMenuItem : public MenuItem {

		// Reference to game state to change the state
		GameState&			_gameState;

	public:
		// Constructors --
		ExitGameMenuItem(GameState &gameState, Vector2D<uint_fast32_t> const pos, std::string const &sprite);
		ExitGameMenuItem(ExitGameMenuItem const &src);
		~ExitGameMenuItem(void);

		// Overload operators --
		ExitGameMenuItem	&operator=(ExitGameMenuItem const &rhs);

		// Getters --
		GameState			&getGameState(void) const;

	protected:

		// Override Menu Item execute code
		void				_execute(void);

	};

	// To print the game state info
	std::ostream      	&operator<<(std::ostream &o, ExitGameMenuItem const &i);

#endif
