#ifndef MENU_HANDLER_CLASS_HPP
	#define MENU_HANDLER_CLASS_HPP

	// Forward declaring classes
	template<typename T> class	Vector2D;
	class						Menu;

	class MenuHandler {

		static Menu*		_menu;

	public:

		// Getters --
		static Menu*		getMenu(void);

		// Setters --
		static void 		setMenu(unsigned type);

		// Destroyers --
		static void			deleteMenu(void);

		// Menu operator setters --
		static void			getNextItem(void);
		static void			getPrevItem(void);

		// Helper Methods --
		static void			handleResize(void);
		static void			execute(void);

	};

	// To print the game state info
	std::ostream      			&operator<<(std::ostream &o, MenuHandler const &i);

#endif
