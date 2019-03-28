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
#include "PathFollower.class.hpp"
#include "GameEngine.class.hpp"
#include "Timers/AsynFuncTimer.class.hpp"

PathFollower::PathFollower(Maze& maze, std::vector<Vector2D<uint_fast32_t>> path) : Actor(maze.convToWorldCoords(path[0]), PATH_FOLLOWER), _maze(maze), _timer(new AsynFuncTimer(std::bind(&PathFollower::followPath, this), 3000)), _index(0), _path(path) {
	_timer->start();
	return;
}

PathFollower::PathFollower(PathFollower const &src) : Actor(src), _maze(src.getMaze()) {
	*this = src;
}

PathFollower::~PathFollower(void) {
	delete _timer;
	return;
}

PathFollower							&PathFollower::operator=(PathFollower const &rhs) {
	if (this != &rhs) {
		this->_path = rhs.getPath();
	}
	return *this;
}

// Getters --
Maze&									PathFollower::getMaze(void) const {
	return _maze;
}

std::vector<Vector2D<uint_fast32_t>>	PathFollower::getPath(void) const {
	return _path;
}

void									PathFollower::followPath(void) {
	if (_index >= _path.size()) return;
	setPos(_maze.convToWorldCoords(_path[_index]));
	_maze.addCharToMaze(_path[_index], (_index == 0) ? 'S' : 'P');
	_index++;
}

void 									PathFollower::draw(void) {
	GameEngine::usePathFollowerAttr(true);
	GameObject::draw();
	GameEngine::usePathFollowerAttr(false);
}

void									PathFollower::tick(void) {
	return;
}
