#ifndef EXIT_GAME_ITEM_CLASS_HPP
	#define EXIT_GAME_ITEM_CLASS_HPP

	#include "MenuItem.class.hpp"

	class ExitGameItem : public MenuItem {

		public:
		// Constructors --
		ExitGameItem(Vector2D<uint_fast32_t> const pos);
		ExitGameItem(ExitGameItem const &src);
		~ExitGameItem(void);

		// Overload operators --
		ExitGameItem	&operator=(ExitGameItem const &rhs);

	protected:

		// Abstract method for the derived class
		void			_execute(void) override;

	};

	// To print the game state info
	std::ostream      	&operator<<(std::ostream &o, ExitGameItem const &i);

#endif
