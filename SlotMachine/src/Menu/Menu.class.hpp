#ifndef MENU_CLASS_HPP
	#define MENU_CLASS_HPP

	#include <includes.hpp>
	#include <vector>

	// Forward declaring classes
	template<typename T> class	Vector2D;
	class						GameObject;
	class						MenuItem;

	class Menu {

		// The selected item index
		unsigned int			_itemIndex;
		// All items in the menu
		std::vector<MenuItem*>	_items;
		// A game object acting as title
		GameObject*				_title;
		// Is the menu horizontal
		bool					_bIsHorizontal;

	public:
		// Constructors --
		Menu(std::string const title, std::vector<int> const items, bool bIsHorizontal);
		Menu(Menu const &src);
		~Menu(void);

		// Overload operators --
		Menu					&operator=(Menu const &rhs);

		// Getters --
		unsigned int			getItemIndex(void) const;
		std::vector<MenuItem*>	getAllItems(void) const;
		GameObject*				getTitle(void) const;
		bool					getIsHorizontal(void) const;

		// Setters --
		void 					resetPos(void);

		// Input setters --
		void					increaseIndexItem(void);
		void					decreaseIndexItem(void);

		// Helper Methods --
		void					executeSelected(void);

	private:

		// Private Initializer func --
		void					_createTitle(Vector2D<uint_fast32_t> pos, std::string const title);
		void					_createItems(std::vector<int> const items);

		// Private helper Methods --
		MenuItem*				_chooseMenuItem(unsigned int i, unsigned int vLen, int const item);
		Vector2D<uint_fast32_t>	_createVerticalList(unsigned int i, unsigned int vecLen);
		Vector2D<uint_fast32_t>	_createHorizontalList(unsigned int i, unsigned int vecLen, unsigned int strLen);
		void					_resetSelectedIndex(void);

		// Private delete funcs --
		void					_deleteTitle(void);
		void					_deleteItems(void);

	};

	// To print the game state info
	std::ostream      			&operator<<(std::ostream &o, Menu const &i);

#endif
