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
			_menu = new Menu("Maze Crawler", { 0 }, false);
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
void				MenuHandler::getNextItem(void) {
	if(_menu) _menu->increaseIndexItem();
}

void				MenuHandler::getPrevItem(void) {
	if(_menu) _menu->decreaseIndexItem();
}

void				MenuHandler::handleResize(void) {
	if(_menu) _menu->resetPos();
}

// To execute the code base on the item choosen
void				MenuHandler::execute(void) {
	if(_menu) _menu->executeSelected();
}

// Overload the output operator for testing
std::ostream      			&operator<<(std::ostream &o, MenuHandler const &i) {
	return o << "Menu Handler Info:" << std::endl <<
	"menu: " << i.getMenu() << std::endl;
}