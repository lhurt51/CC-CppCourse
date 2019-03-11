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

#include "Vector2D.class.hpp"
#include "GameState.class.hpp"
#include "MenuItem.class.hpp"
#include "MenuHandler.class.hpp"

MenuHandler::MenuHandler(GameState &state, std::string const &title) : _state(state), _title(title) {
	return;
}

MenuHandler::MenuHandler(MenuHandler const &src) : _state(src.getGameState()), _title(src.getTitle()) {
	*this = src;
	return;
}

MenuHandler::~MenuHandler(void) {
	return;
}

// Overload operators --
MenuHandler				&MenuHandler::operator=(MenuHandler const &rhs) {
	if (this != &rhs) {
		this->_itemIndex = rhs.getItemIndex();
		this->_items = rhs.getAllItems();
	}
	return *this;
}

GameState				&MenuHandler::getGameState(void) const {
	return this->_state;
}

std::string const		&MenuHandler::getTitle(void) const {
	return this->_title;
}

// Getters --
unsigned int			MenuHandler::getItemIndex(void) const {
	return this->_itemIndex;
}

std::vector<MenuItems*>	MenuHandler::getAllItems(void) const {
	return this->_items;
}

// Setters --
void					MenuHandler::setIndexItem(unsigned int const index) {
	this->_itemIndex = index;
}

void					MenuHandler::setAllItems(std::vector<MenuItems*> const items) {
	this->_items = items;
}

// Helper Methods --
void					MenuHandler::updateMenus(void) {

}
