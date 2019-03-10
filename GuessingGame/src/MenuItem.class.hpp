#ifndef MENU_ITEM_CLASS_HPP
	#define MENU_ITEM_CLASS_HPP

	#include <includes.hpp>

	// Forward declaring classes
	template<typename T>
    class Vector2D;

	class Actor;

	class MenuItem : public Actor {

		bool			_bIsSelected;

	public:
		// Constructors --
		MenuItem(Vector2D<uint_fast32_t> const pos, std::string const &sprite);
		MenuItem(GameState const &src);
		~MenuItem(void);

		// Overload operators --
		MenuItem		&operator=(MenuItem const &rhs);

		// Getters --

		// Setters --
		void			setIsSelected(bool const bIsSelected);

	};

	// To print the game state info
	std::ostream      					&operator<<(std::ostream &o, MenuItem const &i);

#endif
