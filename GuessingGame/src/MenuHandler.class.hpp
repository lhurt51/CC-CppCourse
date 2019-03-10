#ifndef MENU_HANDLER_CLASS_HPP
	#define MENU_HANDLER_CLASS_HPP

	#include <includes.hpp>
	#include <vector>

	// Forward declaring classes
	template<typename T>
    class Vector2D;

	class MenuItems;

	class MenuHandler {

		GameState&			_state;
		unsigned int		_itemIndex;
		vector<MenuItems*>	_items;

	public:
		// Constructors --
		MenuHandler(GameState &state);
		MenuHandler(GameState const &src);
		~MenuHandler(void);

		// Overload operators --
		MenuHandler			&operator=(MenuHandler const &rhs);

		// Getters --
		unsigned int		getItemIndex(void) const;
		vector<MenuItems*>	getAllItems(void) const;

		// Setters --
		void				setIndexItem(unsigned int const index);
		void				setAllItems(vector<MenuItems*> const items);

		// Helper Methods --
		void				updateMenus(void);

	};

	// To print the game state info
	std::ostream      		&operator<<(std::ostream &o, MenuHandler const &i);

#endif
