#ifndef MAIN_MENU_ITEM_CLASS_HPP
	#define MAIN_MENU_ITEM_CLASS_HPP

	#include "MenuItem.class.hpp"

	class MainMenuItem : public MenuItem {

		public:
		// Constructors --
		MainMenuItem(Vector2D<uint_fast32_t> const pos);
		MainMenuItem(MainMenuItem const &src);
		~MainMenuItem(void);

		// Overload operators --
		MainMenuItem	&operator=(MainMenuItem const &rhs);

	protected:

		// Abstract method for the derived class
		void			_execute(void) override;

	};

	// To print the game state info
	std::ostream      	&operator<<(std::ostream &o, MainMenuItem const &i);

#endif
