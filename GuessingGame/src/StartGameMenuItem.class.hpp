#ifndef START_GAME_MENU_ITEM_CLASS_HPP
	#define START_GAME_MENU_ITEM_CLASS_HPP

	#include <includes.hpp>
	#include "MenuItem.class.hpp"

	class 					GameState;

	class StartGameMenuItem : public MenuItem {

		// Reference to game state to change the state
		GameState&			_gameState;

	public:
		// Constructors --
		StartGameMenuItem(GameState &gameState, Vector2D<uint_fast32_t> const pos, std::string const &sprite);
		StartGameMenuItem(StartGameMenuItem const &src);
		~StartGameMenuItem(void);

		// Overload operators --
		StartGameMenuItem	&operator=(StartGameMenuItem const &rhs);

		// Getters --
		GameState			&getGameState(void) const;

	protected:

		// Override Menu Item execute code
		void				_execute(void);

	};

	// To print the game state info
	std::ostream      	&operator<<(std::ostream &o, StartGameMenuItem const &i);

#endif
