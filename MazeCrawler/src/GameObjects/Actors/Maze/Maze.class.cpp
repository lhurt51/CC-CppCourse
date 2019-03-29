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
#include "PathFollower.class.hpp"
#include "Maze.class.hpp"
#include "GameEngine.class.hpp"

Maze::Maze(Vector2D<uint_fast32_t> pos) : Actor(pos, BOARD_SPRITE), _bFoundPath(false), _spriteDim(GameEngine::gameObjectSpriteDim(BOARD_SPRITE)), _follower(nullptr) {
	setSpriteDim();
	_initFollower();
	return;
}

Maze::Maze(Maze const &src) : Actor(src) {
	*this = src;
}

Maze::~Maze(void) {
	_deleteFollower();
	_path.clear();
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
	_spriteDim = GameEngine::gameObjectSpriteDim(_sprite);
}

void					Maze::setPos(Vector2D<uint_fast32_t> pos) {
	Actor::setPos(pos);
	if (_follower && _follower->getIndex() < _follower->getPath().size()) {
		_follower->setPos(convToWorldCoords(_follower->getPath()[_follower->getIndex()]));
	}
}

Vector2D<uint_fast32_t> Maze::convToWorldCoords(Vector2D<uint_fast32_t> boardCoords) {
	return (_pos - (_spriteDim / (unsigned)2) + boardCoords);
}

bool					Maze::findPath(std::string sprite, Vector2D<int> startingPos) {
	if (startingPos.x < 0 || startingPos.x >= (int)_spriteDim.x || startingPos.y < 0 || startingPos.y >= (int)_spriteDim.y)
        return false;
	if (startingPos.y * (_spriteDim.x + 1) + startingPos.x >= sprite.length() || sprite[startingPos.y * (_spriteDim.x + 1) + startingPos.x] != '.')
		return false;
	sprite[startingPos.y * (_spriteDim.x + 1) + startingPos.x] = (startingPos.x == 0) ? 'S' : 'P';
	_path.push_back(Vector2D<uint_fast32_t>(startingPos.x, startingPos.y));
	if (startingPos.x == (int)_spriteDim.x - 1)
        return true;
	if (findPath(sprite, Vector2D<int>(startingPos.x + 2, startingPos.y)))
        return true;
	if (findPath(sprite, Vector2D<int>(startingPos.x, startingPos.y + 1)))
        return true;
    if (findPath(sprite, Vector2D<int>(startingPos.x, startingPos.y - 1)))
        return true;
    if (findPath(sprite, Vector2D<int>(startingPos.x - 2, startingPos.y)))
        return true;
	sprite[startingPos.y * (_spriteDim.x + 1) + startingPos.x] = 'E';
	return false;
}

void 					Maze::addCharToMaze(Vector2D<uint_fast32_t> boardCoords, char c) {
	std::string sprite = _sprite;
	if (boardCoords.x >= _spriteDim.x || boardCoords.y >= _spriteDim.y) return;
	sprite[boardCoords.y * (_spriteDim.x + 1) + boardCoords.x] = c;
	setSprite(sprite);
}

void					Maze::tick(void) {
	if (_follower && _follower->getIndex() >= _follower->getPath().size())
		_deleteFollower();
	return;
}

void					Maze::_initFollower(void) {
	if (!_follower) {
		if (!_bFoundPath)
			_bFoundPath = findPath(_sprite, Vector2D<int>(0, 2));
		_follower = new PathFollower(*this, _path);
	}
}

void					Maze::_deleteFollower(void) {
	if (_follower) {
		delete _follower;
		_follower = nullptr;
	}
}
