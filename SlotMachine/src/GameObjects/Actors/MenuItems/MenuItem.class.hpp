#ifndef MENU_ITEM_CLASS_HPP
	#define MENU_ITEM_CLASS_HPP

	 #include "GameObjects/Actors/Actor.class.hpp"

	class MenuItem : public Actor {

		// Is the item selected
		bool			_bIsSelected;
		// Should the item execute
		bool			_bShouldExec;

		public:
		// Constructors --
		MenuItem(Vector2D<uint_fast32_t> const pos, std::string const &sprite);
		MenuItem(MenuItem const &src);
		~MenuItem(void);

		// Overload operators --
		MenuItem		&operator=(MenuItem const &rhs);

		// Getters --
		bool			getIsSelected(void) const;
		bool			getShouldExec(void) const;

		// Setters --
		void			setIsSelected(bool const bIsSelected);
		void			setShouldExec(bool const bShouldExec);

		// Actor abstract method implementation
		void			tick(void) override;
		virtual void 	draw(void) override;

	protected:

		// Abstract method for the derived class
		virtual void	_execute(void) = 0;

	};

	// To print the game state info
	std::ostream      	&operator<<(std::ostream &o, MenuItem const &i);

#endif
