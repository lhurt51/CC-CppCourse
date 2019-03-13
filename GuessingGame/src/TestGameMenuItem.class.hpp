#ifndef TEST_GAME_MENU_ITEM_CLASS_HPP
	#define TEST_GAME_MENU_ITEM_CLASS_HPP

	#include <includes.hpp>
	#include "MenuItem.class.hpp"

	class 					GameState;

	class TestGameMenuItem : public MenuItem {

		// Reference to game state to change the state
		GameState&			_gameState;

	public:
		// Constructors --
		TestGameMenuItem(GameState &gameState, Vector2D<uint_fast32_t> const pos, std::string const &sprite);
		TestGameMenuItem(TestGameMenuItem const &src);
		~TestGameMenuItem(void);

		// Overload operators --
		TestGameMenuItem	&operator=(TestGameMenuItem const &rhs);

		// Getters --
		GameState			&getGameState(void) const;

	protected:

		// Override Menu Item execute code
		void				_execute(void);

	};

	// To print the game state info
	std::ostream      	&operator<<(std::ostream &o, TestGameMenuItem const &i);

#endif
