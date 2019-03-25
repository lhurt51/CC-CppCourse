#ifndef START_GAME_ITEM_CLASS_HPP
	#define START_GAME_ITEM_CLASS_HPP

	#include "MenuItem.class.hpp"

	class StartGameItem : public MenuItem {

		public:
		// Constructors --
		StartGameItem(Vector2D<uint_fast32_t> const pos);
		StartGameItem(StartGameItem const &src);
		~StartGameItem(void);

		// Overload operators --
		StartGameItem	&operator=(StartGameItem const &rhs);

	protected:

		// Abstract method for the derived class
		void			_execute(void);

	};

	// To print the game state info
	std::ostream      	&operator<<(std::ostream &o, StartGameItem const &i);

#endif
