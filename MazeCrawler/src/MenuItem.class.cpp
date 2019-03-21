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

#include "Vector2D.class.hpp"
#include "MenuItem.class.hpp"

// Default constructors to initialize the pos and sprite
MenuItem::MenuItem(Vector2D<uint_fast32_t> const pos, std::string const &sprite) : Actor(pos, sprite), _bIsSelected(false), _bShouldExec(false) {
	return;
}

// Copy constructor
MenuItem::MenuItem(MenuItem const &src) : Actor(src) {
	*this = src;
	return;
}

// Deconstructor
MenuItem::~MenuItem(void) {
	return;
}

// Overload equals operator
MenuItem		&MenuItem::operator=(MenuItem const &rhs) {
	if (this != &rhs) {
		this->_bIsSelected = rhs.getIsSelected();
		this->_bShouldExec = rhs.getShouldExec();
	}
	return *this;
}

// Getters --
bool			MenuItem::getIsSelected(void) const {
	return this->_bIsSelected;
}

bool			MenuItem::getShouldExec(void) const {
	return this->_bShouldExec;
}

// Setters --
void			MenuItem::setIsSelected(bool const bIsSelected) {
	if (this->_bIsSelected == bIsSelected) return;
	this->_bIsSelected = bIsSelected;
	this->_bNeedsUpdate = true;
}

void			MenuItem::setShouldExec(bool const bShouldExec) {
	if (!this->_bIsSelected) return;
	this->_bShouldExec = bShouldExec;
	this->_bNeedsUpdate = true;
}

// Actor abstract method implementation to execute code base on bShouldExec
void			MenuItem::tick(void) {
	if (_bShouldExec) {
		_execute();
		_bShouldExec = false;
	}
}
