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

		// Helper Methods --
		static void			handleInput(int input);
		static void			handleResize(void);

	};

	// To print the game state info
	std::ostream      			&operator<<(std::ostream &o, MenuHandler const &i);

#endif
