#ifndef MENU_HANDLER_CLASS_HPP
	#define MENU_HANDLER_CLASS_HPP

	#include <includes.hpp>
	#include <vector>

	// Forward declaring classes
	template<typename T>
    class Vector2D;

	class MenuItems;
	class GameState;

	class MenuHandler {

		GameState&				_state;
		std::string const&		_title;
		unsigned int			_itemIndex;
		std::vector<MenuItems*>	_items;

	public:
		// Constructors --
		MenuHandler(GameState &state, std::string const &title);
		MenuHandler(MenuHandler const &src);
		~MenuHandler(void);

		// Overload operators --
		MenuHandler				&operator=(MenuHandler const &rhs);

		// Getters --
		GameState				&getGameState(void) const;
		std::string const		&getTitle(void) const;
		unsigned int			getItemIndex(void) const;
		std::vector<MenuItems*>	getAllItems(void) const;

		// Setters --
		void					setIndexItem(unsigned int const index);
		void					setAllItems(std::vector<MenuItems*> const items);

		// Helper Methods --
		void					updateMenus(void);

	};

	// To print the game state info
	std::ostream      		&operator<<(std::ostream &o, MenuHandler const &i);

#endif
