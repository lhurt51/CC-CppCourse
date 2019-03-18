/******************************************************************************
* Programmer Name:
* Liam Hurt
*
* Date:
* 2/6/2019
*
* Assignment Requirement:
* - Ask the user to guess a whole number between 1 and 1000 or character 'A'
*   to 'Z'
* - Your program will try to find the number
* - Keep track of the number of guesses by the computer
* - Use Recursive one of two search techniques: linear search or binary search
*   or randomize guess of a number.
* - Use a template class so the program could be used for integer or character,
*   your test function within your class should run with integer first then a
*   character
* - Use a randomized random number or letter generator for the item to guess
* - Allow the computer to have only 15 guesses
* - Your game class will have two functions or methods: playTheGame and static
*   Test
* - Your game shall have two modes: automatic where the computer tries to guess
*   you number without any input from you (except for the guess number) and
*   manual mode where each guess of the computer requires your input of Higher,
*   Lower, Right
*
******************************************************************************/

/*
#include <typedefs.hpp>
#include "Vector2D.class.hpp"
#include "GameState.class.hpp"
#include "MenuItem.class.hpp"
#include "MenuHandler.class.hpp"

// Default constructor to init the state and items
MenuHandler::MenuHandler(GameState &state, std::string const title, std::vector<std::string> const items, bool bIsHorizontal) : Actor(Vector2D<uint_fast32_t>(HALF_OF_VAL(state.getWinDem().x), 5), title), _state(state), _itemIndex(0), _bIsHorizontal(bIsHorizontal) {
	_createItems(items);
	_resetSelectedIndex();
	return;
}

// Copy constructor
MenuHandler::MenuHandler(MenuHandler const &src) : Actor(src), _state(src.getGameState()) {
	*this = src;
	return;
}

// Default deconstructor to delete the items
MenuHandler::~MenuHandler(void) {
	_deleteItems();
	return;
}

// Overload operators --
MenuHandler				&MenuHandler::operator=(MenuHandler const &rhs) {
	if (this != &rhs) {
		this->_state = rhs.getGameState();
		this->_itemIndex = rhs.getItemIndex();
		this->_items = rhs.getAllItems();
		this->_bIsHorizontal = rhs.getIsHorizontal();
	}
	return *this;
}

// Getters --
GameState				&MenuHandler::getGameState(void) const {
	return this->_state;
}

unsigned int			MenuHandler::getItemIndex(void) const {
	return this->_itemIndex;
}

std::vector<MenuItem*>	MenuHandler::getAllItems(void) const {
	return this->_items;
}

bool					MenuHandler::getIsHorizontal(void) const {
	return this->_bIsHorizontal;
}

// Setters --
void					MenuHandler::increaseIndexItem(void) {
	this->_itemIndex++;
	if (this->_itemIndex >= _items.size()) this->_itemIndex = 0;
	_resetSelectedIndex();
}

void					MenuHandler::decreaseIndexItem(void) {
	this->_itemIndex--;
	if (this->_itemIndex >= this->_items.size()) this->_itemIndex = this->_items.size() - 1;
	_resetSelectedIndex();
}

// Helper Methods --
// To execute the code base on the item choosen
void					MenuHandler::doExecute(void) {
	_items[_itemIndex]->setShouldExec(true);
}

// Update the menu items every redraw
void					MenuHandler::tick(void) {
	setPos(Vector2D<uint_fast32_t>(HALF_OF_VAL(_state.getWinDem().x), HALF_OF_VAL(_state.getWinDem().y) - ((_bIsHorizontal) ? MENU_ITEM_SPACE : ((HALF_OF_VAL(_items.size()) + MENU_ITEM_SPACE) * MENU_ITEM_SPACE))));
	for (unsigned i = 0; i < _items.size(); i++) {
		_items[i]->setPos((_bIsHorizontal) ? _createHorizontalList(i, _items.size(), _items[i]->getSprite().length()) : _createVerticalList(i, _items.size()));
	}
}

// Private helper Methods --
// Create the list of menu items
void					MenuHandler::_createItems(std::vector<std::string> const items) {
	for (unsigned i = 0; i < items.size(); i++)
		_items.push_back(_chooseMenuItem(i, items.size(), items[i]));
}

// Choose the class of menu item based on state
MenuItem*				MenuHandler::_chooseMenuItem(unsigned int i, unsigned int vLen, std::string const item) {
	if (item[i] == item[vLen]) return nullptr;
	switch(_state.getCurState()) {
		default:
			if (item[i] == item[vLen]) return nullptr;
			break;
	}
	return nullptr;
}

// To create the vector pos for a vertical menu list
Vector2D<uint_fast32_t>	MenuHandler::_createVerticalList(unsigned int i, unsigned int vecLen) {
	return Vector2D<uint_fast32_t>(HALF_OF_VAL(_state.getWinDem().x), HALF_OF_VAL(_state.getWinDem().y) - vecLen + (i * MENU_ITEM_SPACE));
}

// To create the vector pos for a horizontal menu list
Vector2D<uint_fast32_t>	MenuHandler::_createHorizontalList(unsigned int i, unsigned int vecLen, unsigned int strLen) {
	return Vector2D<uint_fast32_t>(HALF_OF_VAL(_state.getWinDem().x) - (HALF_OF_VAL(vecLen) * HALF_OF_VAL(strLen) + HALF_OF_VAL(MENU_ITEM_SPACE * (vecLen - 1))) + (i * strLen) + (i * MENU_ITEM_SPACE), HALF_OF_VAL(_state.getWinDem().y));
}

// To reset the selected index for all menu items
void					MenuHandler::_resetSelectedIndex(void) {
	for (unsigned i = 0; i < _items.size(); i++) {
		if (_itemIndex == i) _items[i]->setIsSelected(true);
		else _items[i]->setIsSelected(false);
	}
}

// To delete all items
void					MenuHandler::_deleteItems(void) {
	for (std::vector<MenuItem*>::iterator pObj = _items.begin(); pObj != _items.end(); ++pObj)
		delete *pObj;
	_items.clear();
}

// Overload the output operator for testing
std::ostream      			&operator<<(std::ostream &o, MenuHandler const &i) {
	return o << "Menu Handler Info:" << std::endl <<
	"game state: " << i.getGameState() << std::endl <<
	"selected index: " << i.getItemIndex() << std::endl;
}
*/
