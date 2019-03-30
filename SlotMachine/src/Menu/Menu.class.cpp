/*******************************************************************************\
* Programmer Name:																*
* Liam Hurt																		*
*																				*
* Date:																			*
* 3/28/2019																		*
*																				*
* Assignment Requirement:														*
* This program will play a slot machine game. The slot machine shall have 3     *
* slots (or a single number between 0 to 9 for each slot) of the following      *
* ASCII number vector to use (see below). The user shall have the ability to    *
* make a bet and then the game will automatically spin the digits. Use a delay  *
* to simulate the numbers changing before the final numbers are revealed (if    *
* you use C++ 11 see the function below). The following conditions will be      *
* programmed:                                                                   *
*                                                                               *
* 3 matching numbers win 10 times the bet                                       *
*                                                                               *
* 2 matching numbers win 5 times the bet                                        *
*                                                                               *
* no matching number losses the bet				                     			*
*																				*
\*******************************************************************************/

#include <macros/menu_macros.hpp>
#include "Vector2D.class.hpp"
#include "GameObjects/Actors/MenuItems/StartGameItem.class.hpp"
#include "GameObjects/Actors/MenuItems/ExitGameItem.class.hpp"
#include "GameObjects/Actors/MenuItems/MainMenuItem.class.hpp"
#include "Menu.class.hpp"
#include "Handlers/GameStateHandler.class.hpp"

// Default constructor to init the state and items
Menu::Menu(std::string const title, std::vector<int> const items, bool bIsHorizontal) : _itemIndex(0), _bIsHorizontal(bIsHorizontal) {
	_title = nullptr;
	_createTitle(Vector2D<uint_fast32_t>(HALF_OF_VAL(GameStateHandler::getWinDim().x), HALF_OF_VAL(GameStateHandler::getWinDim().y) - ((bIsHorizontal) ? (-5 + MENU_ITEM_SPACE) : ((HALF_OF_VAL(items.size()) + MENU_ITEM_SPACE) * MENU_ITEM_SPACE))), title);
	_createItems(items);
	_resetSelectedIndex();
	return;
}

// Copy constructor
Menu::Menu(Menu const &src) {
	*this = src;
	return;
}

// Default deconstructor to delete the items
Menu::~Menu(void) {
	_deleteTitle();
	_deleteItems();
	return;
}

// Overload operators --
Menu					&Menu::operator=(Menu const &rhs) {
	if (this != &rhs) {
		this->_itemIndex = rhs.getItemIndex();
		this->_items = rhs.getAllItems();
		this->_bIsHorizontal = rhs.getIsHorizontal();
	}
	return *this;
}

// Getters --
unsigned int			Menu::getItemIndex(void) const {
	return this->_itemIndex;
}

std::vector<MenuItem*>	Menu::getAllItems(void) const {
	return this->_items;
}

GameObject*				Menu::getTitle(void) const {
	return this->_title;
}

bool					Menu::getIsHorizontal(void) const {
	return this->_bIsHorizontal;
}

// Setters --
void 					Menu::resetPos(void) {
	if (_title) _title->setPos(Vector2D<uint_fast32_t>(HALF_OF_VAL(GameStateHandler::getWinDim().x), HALF_OF_VAL(GameStateHandler::getWinDim().y) - ((_bIsHorizontal) ? (-5 + MENU_ITEM_SPACE) : ((HALF_OF_VAL(_items.size()) + MENU_ITEM_SPACE) * MENU_ITEM_SPACE))));
	for (unsigned i = 0; i < _items.size(); i++) {
		if (_items[i]) _items[i]->setPos((_bIsHorizontal) ? _createHorizontalList(i, _items.size(), _items[i]->getSprite().length()) : _createVerticalList(i, _items.size()));
	}
}

void					Menu::increaseIndexItem(void) {
	this->_itemIndex++;
	if (this->_itemIndex >= _items.size()) this->_itemIndex = 0;
	_resetSelectedIndex();
}

void					Menu::decreaseIndexItem(void) {
	this->_itemIndex--;
	if (this->_itemIndex >= this->_items.size()) this->_itemIndex = this->_items.size() - 1;
	_resetSelectedIndex();
}

// Helper Methods --
// To execute the code base on the item choosen
void					Menu::executeSelected(void) {
	if (_items[_itemIndex]) _items[_itemIndex]->setShouldExec(true);
}

// Private helper Methods --
void					Menu::_createTitle(Vector2D<uint_fast32_t> pos, std::string const title) {
	if (!_title) _title = new GameObject(pos, title);
}

// Create the list of menu items
void					Menu::_createItems(std::vector<int> const items) {
	for (unsigned i = 0; i < items.size(); i++)
		_items.push_back(_chooseMenuItem(i, items.size(), items[i]));
}

// Choose the class of menu item based on state
MenuItem*				Menu::_chooseMenuItem(unsigned int i, unsigned int vLen, int const item) {
	switch(item) {
		case 0:
			return new StartGameItem((_bIsHorizontal) ? _createHorizontalList(i, vLen, std::string("Start").length()) : _createVerticalList(i, vLen));
		case 1:
			return new ExitGameItem((_bIsHorizontal) ? _createHorizontalList(i, vLen, std::string("Exit").length()) : _createVerticalList(i, vLen));
		case 2:
			return new MainMenuItem((_bIsHorizontal) ? _createHorizontalList(i, vLen, std::string("Back").length()) : _createVerticalList(i, vLen));
		default:
			return nullptr;
	}
}

// To create the vector pos for a vertical menu list
Vector2D<uint_fast32_t>	Menu::_createVerticalList(unsigned int i, unsigned int vecLen) {
	return Vector2D<uint_fast32_t>(HALF_OF_VAL(GameStateHandler::getWinDim().x), HALF_OF_VAL(GameStateHandler::getWinDim().y) - vecLen + (i * MENU_ITEM_SPACE));
}

// To create the vector pos for a horizontal menu list
Vector2D<uint_fast32_t>	Menu::_createHorizontalList(unsigned int i, unsigned int vecLen, unsigned int strLen) {
	return Vector2D<uint_fast32_t>(HALF_OF_VAL(GameStateHandler::getWinDim().x) - (HALF_OF_VAL(vecLen) * HALF_OF_VAL(strLen) + HALF_OF_VAL(MENU_ITEM_SPACE * (vecLen - 1))) + (i * strLen) + (i * MENU_ITEM_SPACE), HALF_OF_VAL(GameStateHandler::getWinDim().y) + 5);
}

// To reset the selected index for all menu items
void					Menu::_resetSelectedIndex(void) {
	for (unsigned i = 0; i < _items.size(); i++) {
		if (_items[i]) _items[i]->setIsSelected((_itemIndex == i) ? true : false);
	}
}

void					Menu::_deleteTitle(void) {
	if (_title) {
		delete _title;
		_title = nullptr;
	}
}

// To delete all items
void					Menu::_deleteItems(void) {
	if (_items.empty()) return;
	for (std::vector<MenuItem*>::iterator pObj = _items.begin(); pObj != _items.end(); ++pObj)
		delete *pObj;
	_items.clear();
}

// Overload the output operator for testing
std::ostream      			&operator<<(std::ostream &o, Menu const &i) {
	return o << "Menu Handler Info:" << std::endl <<
	"selected index: " << i.getItemIndex() << std::endl;
}
