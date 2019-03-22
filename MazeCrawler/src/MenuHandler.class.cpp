/*******************************************************************************\
* Programmer Name:																*
* Liam Hurt																		*
*																				*
* Date:																			*
* 3/16/2019																		*
*																				*
* Assignment Requirement:														*
* 7.33 (Maze Traversal) The grid of hashes (#) and dots (.) in Fig. 7.29 is a	*
* two-dimensional builtin array representation of a maze. In the				*
* two-dimensional built-in array, the hashes represent the walls of the maze	*
* and the dots represent squares in the possible paths through the maze. Moves	*
* can be made only to a location in the built-in array that contains a dot.		*
* There is a simple algorithm for walking through a maze that guarantees to		*
* find the exit (assuming that there is an exit). If there is not an exit,		*
* you’ll arrive at the starting location again. Place your right hand on		*
* the wall to your right and begin walking forward. Never remove your hand		*
* from the wall. If the maze turns to the right, you follow the wall to the		*
* right. As long as you do not remove your hand from the wall, eventually		*
* you’ll arrive at the exit of the maze. There may be a shorter path than the	*
* one you’ve taken, but you are guaranteed to get out of the maze if you		*
* follow the algorithm.															*
*																				*
*  # # # # # # # # # # # #														*
*  # . . . # . . . . . . #														*
*  . . # . # . # # # # . #														*
*  # # # . # . . . . # . #														*
*  # . . . . # # # . # . .														*
*  # # # # . # . # . # . #														*
*  # . . # . # . # . # . #														*
*  # # . # . # . # . # . #														*
*  # . . . . . . . . # . #														*
*  # # # # # # . # # # . #														*
*  # . . . . . . # . . . #														*
*  # # # # # # # # # # # #														*
*																				*
* Write recursive function mazeTraverse to walk through the maze. The function	*
* should receive arguments that include a 12-by-12 built-in array of chars		*
* representing the maze and the starting location of the maze. As mazeTraverse	*
* attempts to locate the exit from the maze, it should place the character X	*
* in each square in the path. The function should display the maze after each	*
* move, so the user can watch as the maze is solved.							*
*																				*
\*******************************************************************************/

#include <macros/menu_macros.hpp>
#include "Vector2D.class.hpp"
#include "MenuItem.class.hpp"
#include "MenuHandler.class.hpp"
#include "GameStateHandler.class.hpp"

// Vector2D<uint_fast32_t>(HALF_OF_VAL(GameStateHandler::getWinDim().x), 5)
// Default constructor to init the state and items
MenuHandler::MenuHandler(std::string const title, std::vector<std::string> const items, bool bIsHorizontal) : _itemIndex(0), _title(nullptr), _bIsHorizontal(bIsHorizontal) {
	_createTitle(Vector2D<uint_fast32_t>(HALF_OF_VAL(GameStateHandler::getWinDim().x), 5), title);
	_createItems(items);
	_resetSelectedIndex();
	return;
}

// Copy constructor
MenuHandler::MenuHandler(MenuHandler const &src) {
	*this = src;
	return;
}

// Default deconstructor to delete the items
MenuHandler::~MenuHandler(void) {
	_deleteTitle();
	_deleteItems();
	return;
}

// Overload operators --
MenuHandler				&MenuHandler::operator=(MenuHandler const &rhs) {
	if (this != &rhs) {
		this->_itemIndex = rhs.getItemIndex();
		this->_items = rhs.getAllItems();
		this->_bIsHorizontal = rhs.getIsHorizontal();
	}
	return *this;
}

// Getters --
unsigned int			MenuHandler::getItemIndex(void) const {
	return this->_itemIndex;
}

std::vector<MenuItem*>	MenuHandler::getAllItems(void) const {
	return this->_items;
}

GameObject*				MenuHandler::getTitle(void) const {
	return this->_title;
}

bool					MenuHandler::getIsHorizontal(void) const {
	return this->_bIsHorizontal;
}

// Setters --
void 					MenuHandler::resetPos(void) {
	_title->setPos(Vector2D<uint_fast32_t>(HALF_OF_VAL(GameStateHandler::getWinDim().x), HALF_OF_VAL(GameStateHandler::getWinDim().y) - ((_bIsHorizontal) ? MENU_ITEM_SPACE : ((HALF_OF_VAL(_items.size()) + MENU_ITEM_SPACE) * MENU_ITEM_SPACE))));
	for (unsigned i = 0; i < _items.size(); i++) {
		_items[i]->setPos((_bIsHorizontal) ? _createHorizontalList(i, _items.size(), _items[i]->getSprite().length()) : _createVerticalList(i, _items.size()));
	}
}

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

// Private helper Methods --
void					MenuHandler::_createTitle(Vector2D<uint_fast32_t> pos, std::string const title) {
	if (!_title) {
		_title = new GameObject(pos, title);
	}
}

// Create the list of menu items
void					MenuHandler::_createItems(std::vector<std::string> const items) {
	for (unsigned i = 0; i < items.size(); i++)
		_items.push_back(_chooseMenuItem(i, items.size(), items[i]));
}

// Choose the class of menu item based on state
MenuItem*				MenuHandler::_chooseMenuItem(unsigned int i, unsigned int vLen, std::string const item) {
	if (item[i] == item[vLen]) return nullptr;
	/*
	(_bIsHorizontal) ? _createHorizontalList(i, vLen, item.length()) : _createVerticalList(i, vLen);
	switch(_state.getCurState()) {
		default:
			if (item[i] == item[vLen]) return nullptr;
			break;
	}
	*/
	return nullptr;
}

// To create the vector pos for a vertical menu list
Vector2D<uint_fast32_t>	MenuHandler::_createVerticalList(unsigned int i, unsigned int vecLen) {
	return Vector2D<uint_fast32_t>(HALF_OF_VAL(GameStateHandler::getWinDim().x), HALF_OF_VAL(GameStateHandler::getWinDim().y) - vecLen + (i * MENU_ITEM_SPACE));
}

// To create the vector pos for a horizontal menu list
Vector2D<uint_fast32_t>	MenuHandler::_createHorizontalList(unsigned int i, unsigned int vecLen, unsigned int strLen) {
	return Vector2D<uint_fast32_t>(HALF_OF_VAL(GameStateHandler::getWinDim().x) - (HALF_OF_VAL(vecLen) * HALF_OF_VAL(strLen) + HALF_OF_VAL(MENU_ITEM_SPACE * (vecLen - 1))) + (i * strLen) + (i * MENU_ITEM_SPACE), HALF_OF_VAL(GameStateHandler::getWinDim().y));
}

// To reset the selected index for all menu items
void					MenuHandler::_resetSelectedIndex(void) {
	for (unsigned i = 0; i < _items.size(); i++) {
		if (_itemIndex == i) _items[i]->setIsSelected(true);
		else _items[i]->setIsSelected(false);
	}
}

void					MenuHandler::_deleteTitle(void) {
	if (_title) {
		delete _title;
		_title = nullptr;
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
	"selected index: " << i.getItemIndex() << std::endl;
}
