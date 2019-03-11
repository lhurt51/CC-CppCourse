#ifndef MENU_ITEM_CLASS_HPP
	#define MENU_ITEM_CLASS_HPP

	#include <includes.hpp>
	#include "Actor.class.hpp"

	class MenuItem : public Actor {

		bool			_bIsSelected;

	public:
		// Constructors --
		MenuItem(Vector2D<uint_fast32_t> const pos, std::string const &sprite);
		MenuItem(MenuItem const &src);
		~MenuItem(void);

		// Overload operators --
		MenuItem		&operator=(MenuItem const &rhs);

		// Getters --
		bool			getIsSelected(void) const;

		// Setters --
		void			setIsSelected(bool const bIsSelected);

		// Actor abstract method implementation
		void			tick(void);

	};

	// To print the game state info
	std::ostream      					&operator<<(std::ostream &o, MenuItem const &i);

#endif
