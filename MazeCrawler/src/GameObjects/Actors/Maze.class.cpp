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

#include <macros/maze_macros.hpp>
#include "Vector2D.class.hpp"
#include "Maze.class.hpp"
#include "GameEngine.class.hpp"

Maze::Maze(Vector2D<uint_fast32_t> pos) : Actor(pos, BOARD_SPRITE) {
	return;
}

Maze::Maze(Maze const &src) : Actor(src) {
	*this = src;
}

Maze::~Maze(void) {
	return;
}

Maze					&Maze::operator=(Maze const &rhs) {
	if (this != &rhs) {
		this->_bFoundPath = rhs.getFoundPath();
        this->_spriteDim = rhs.getSpriteDim();
	}
	return *this;
}

// Getters --
bool					Maze::getFoundPath(void) const {
	return _bFoundPath;
}

Vector2D<uint_fast32_t>	Maze::getSpriteDim(void) const {
	return _spriteDim;
}

// Setters --
void					Maze::setFoundPath(void) {
	if (!_bFoundPath) _bFoundPath = true;
}

void					Maze::setSpriteDim(void) {
	_spriteDim = GameEngine::gameObjectSpriteDim(getSprite());
}

bool					Maze::findPath(Vector2D<uint_fast32_t> startingPos) {
	if (startingPos.x == _spriteDim.x)
        return true;
	if (_sprite[(startingPos.y * 2) * _spriteDim.x + (startingPos.x * 2)] == '#')
		return false;
    if (startingPos > _spriteDim)
        return false;
    setSprite((std::string&)_sprite[(startingPos.y * 2) * _spriteDim.x + (startingPos.x * 2)] = 'P');
    if (findPath(Vector2D<uint_fast32_t>(startingPos.x + 2, startingPos.y)))
        return true;
    if (findPath(Vector2D<uint_fast32_t>(startingPos.x, startingPos.y - 2)))
        return true;
    if (findPath(Vector2D<uint_fast32_t>(startingPos.x, startingPos.y + 2)))
        return true;
    if (findPath(Vector2D<uint_fast32_t>(startingPos.x - 2, startingPos.y)))
        return true;
    setSprite((std::string&)_sprite[(startingPos.y * 2) * _spriteDim.x + (startingPos.x * 2)] = 'E');
	return false;
}

void					Maze::tick(void) {
	return;
}
