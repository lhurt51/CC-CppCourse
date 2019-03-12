#ifndef MENU_HANDLER_CLASS_HPP
	#define MENU_HANDLER_CLASS_HPP

	#include <includes.hpp>
	#include <vector>

	enum						ItemType {
								STARTING_MENU,
								PLAYING_MENU,
	};

	// Forward declaring classes
	template<typename T> class	Vector2D;
	class						MenuItem;
	class						GameState;

	class MenuHandler {

		GameState&				_state;
		std::string const		_title;
		unsigned int			_itemIndex;
		std::vector<MenuItem*>	_items;

	public:
		// Constructors --
		MenuHandler(GameState &state, std::string const title, std::vector<std::string> const items);
		MenuHandler(MenuHandler const &src);
		~MenuHandler(void);

		// Overload operators --
		MenuHandler				&operator=(MenuHandler const &rhs);

		// Getters --
		GameState				&getGameState(void) const;
		std::string const		getTitle(void) const;
		unsigned int			getItemIndex(void) const;
		std::vector<MenuItem*>	getAllItems(void) const;

		// Setters --
		void					setIndexItem(unsigned int const index);
		void					setAllItems(std::vector<MenuItem*> const items);

		// Helper Methods --
		void					createItems(std::vector<std::string> const items);
		void					updateMenus(void);

	private:

		// Private helper Methods --
		void					_createItems(std::vector<std::string> const items);
		Vector2D<uint_fast32_t>	_createVerticalList(unsigned int i, unsigned int vecLen);
		Vector2D<uint_fast32_t>	_createHorizontalList(unsigned int i, unsigned int vecLen, unsigned int strLen);

	};

	// To print the game state info
	std::ostream      			&operator<<(std::ostream &o, MenuHandler const &i);

#endif
