#ifndef MENU_HANDLER_CLASS_HPP
	#define MENU_HANDLER_CLASS_HPP

	#include <includes.hpp>
	#include <vector>
	#include "GameObject.class.hpp"

	// Forward declaring classes
	template<typename T> class	Vector2D;
	class						MenuItem;
	class						GameState;

	class MenuHandler : public GameObject {

		// The game state so it can reference and act on the state
		GameState&				_state;
		// The selected item index
		unsigned int			_itemIndex;
		// All items in the menu
		std::vector<MenuItem*>	_items;
		// Is the menu horizontal
		bool					_bIsHorizontal;

	public:
		// Constructors --
		MenuHandler(GameState &state, std::string const title, std::vector<std::string> const items, bool bIsHorizontal);
		MenuHandler(MenuHandler const &src);
		~MenuHandler(void);

		// Overload operators --
		MenuHandler				&operator=(MenuHandler const &rhs);

		// Getters --
		GameState				&getGameState(void) const;
		unsigned int			getItemIndex(void) const;
		std::vector<MenuItem*>	getAllItems(void) const;
		bool					getIsHorizontal(void) const;

		// Setters --
		virtual void 			setPos(Vector2D<uint_fast32_t> pos) override;

		// Input setters --
		void					increaseIndexItem(void);
		void					decreaseIndexItem(void);

		// Helper Methods --
		void					doExecute(void);

	private:

		// Private Initializer func --
		void					_createItems(std::vector<std::string> const items);

		// Private helper Methods --
		MenuItem*				_chooseMenuItem(unsigned int i, unsigned int vLen, std::string const item);
		Vector2D<uint_fast32_t>	_createVerticalList(unsigned int i, unsigned int vecLen);
		Vector2D<uint_fast32_t>	_createHorizontalList(unsigned int i, unsigned int vecLen, unsigned int strLen);
		void					_resetSelectedIndex(void);

		// Private delete funcs --
		void					_deleteItems(void);

	};

	// To print the game state info
	std::ostream      			&operator<<(std::ostream &o, MenuHandler const &i);

#endif
