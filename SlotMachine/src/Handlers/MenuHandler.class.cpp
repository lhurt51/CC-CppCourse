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
#include "GameObjects/GameObject.class.hpp"
#include "Menu/Menu.class.hpp"
#include "MenuHandler.class.hpp"
#include "GameStateHandler.class.hpp"

Menu*				MenuHandler::_menu = nullptr;

// Getters --
Menu*				MenuHandler::getMenu(void) {
	return _menu;
}

// Setters --
void 				MenuHandler::setMenu(unsigned type) {
	switch(type) {
		case 0:
			if (!_menu) _menu = new Menu("Main Menu", { 0, 1 }, false);
			break;
		case 1:
			if (!_menu) _menu = new Menu("Playing", { 2, 1 }, true);
			break;
		default:
			break;
	}
}

// Destroyers --
void				MenuHandler::deleteMenu(void) {
	if (_menu) {
		delete _menu;
		_menu = nullptr;
	}
}

// Helper Methods --
void				MenuHandler::handleInput(int input) {
	if (!_menu) return;
	if (_menu->getIsHorizontal()) {
		if (input == 'a') _menu->decreaseIndexItem();
		if (input == 'd') _menu->increaseIndexItem();
	} else {
		if (input == 'w') _menu->decreaseIndexItem();
		if (input == 's') _menu->increaseIndexItem();
	}
	if (input == '\n') _menu->executeSelected();
}

void				MenuHandler::handleResize(void) {
	if(_menu) _menu->resetPos();
}

// Overload the output operator for testing
std::ostream      			&operator<<(std::ostream &o, MenuHandler const &i) {
	return o << "Menu Handler Info:" << std::endl <<
	"menu: " << i.getMenu() << std::endl;
}
