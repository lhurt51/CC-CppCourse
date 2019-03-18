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
********************************************************************************/

#include <typedefs.hpp>
#include "Vector2D.class.hpp"
#include "StaticRunTimeComponent.class.hpp"

// Default constructor
StaticRunTimeComponent::StaticRunTimeComponent(Vector2D<uint_fast32_t> pos, std::string const sprite) : _bCanDraw(true), _bCanClear(false), _bNeedsUpdate(true), _pos(pos), _sprite(sprite) {
	return;
}

// Copy constructor
StaticRunTimeComponent::StaticRunTimeComponent(StaticRunTimeComponent const &src) : _sprite(src.getSprite()) {
	*this = src;
	return;
}

// Default deconstructor
StaticRunTimeComponent::~StaticRunTimeComponent(void) {
	return;
}

// Equal sign overload
StaticRunTimeComponent					&StaticRunTimeComponent::operator=(StaticRunTimeComponent const &rhs) {
	if (this != &rhs) {
		this->_bCanDraw = rhs.getCanDraw();
		this->_bCanClear = rhs.getCanClear();
		this->_bNeedsUpdate = rhs.getNeedsUpdate();
		this->_pos = rhs.getPos();
		(std::string&)this->_sprite = rhs.getSprite();
	}
	return *this;
}

// Getters --
bool					StaticRunTimeComponent::getCanDraw(void) const {
	return this->_bCanDraw;
}

bool					StaticRunTimeComponent::getCanClear(void) const {
	return this->_bCanClear;
}

bool					StaticRunTimeComponent::getNeedsUpdate(void) const {
	return this->_bNeedsUpdate;
}

Vector2D<uint_fast32_t>	StaticRunTimeComponent::getPos(void) const {
	return this->_pos;
}

std::string	const		StaticRunTimeComponent::getSprite(void) const {
	return this->_sprite;
}

// Setters --
void					StaticRunTimeComponent::setCanDraw(bool bCanDraw) {
	if (this->_bCanDraw == bCanDraw) return;
	this->_bCanDraw = bCanDraw;
	this->_bNeedsUpdate = true;
}

void					StaticRunTimeComponent::setCanClear() {
	this->_bCanClear = true;
	this->_bCanDraw = false;
	this->_bNeedsUpdate = true;
}

void					StaticRunTimeComponent::setNeedsUpdate(void) {
	this->_bNeedsUpdate = false;
}

void 					StaticRunTimeComponent::setPos(Vector2D<uint_fast32_t> pos) {
	this->_pos = pos;
	this->_bNeedsUpdate = true;
}

void					StaticRunTimeComponent::setSprite(std::string sprite) {
	if (_sprite == sprite) return;
	(std::string&)this->_sprite = sprite;
	this->_bNeedsUpdate = true;
}

// Output pverload for testing
std::ostream			&operator<<(std::ostream &o, StaticRunTimeComponent const &i) {
	return o << "StaticRunTimeComponent Info:" << std::endl <<
	"can draw: " << i.getCanDraw() << std::endl <<
	"can clear: " << i.getCanClear() << std::endl <<
	"should update: " << i.getNeedsUpdate() << std::endl <<
	"pos: " << i.getPos() << std::endl <<
	"sprite: " << i.getSprite() << std::endl;
}
