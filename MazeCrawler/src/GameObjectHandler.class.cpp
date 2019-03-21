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
#include "GameObject.class.hpp"
#include "GameObjectHandler.class.hpp"

std::vector<GameObject*> 				GameObjectHandler::_allObjects;

unsigned								GameObjectHandler::findIndex(GameObject *obj) {
	unsigned start = 0;

	for(GameObject* tmp : _allObjects) {
		if (tmp == obj)
			return start;
		start++;
	}
	return start;
}

GameObject*								GameObjectHandler::findObject(unsigned index) {
	if (index < _allObjects.size())
		return _allObjects[index];
	return nullptr;
}

void									GameObjectHandler::addObject(GameObject *obj) {
	_allObjects.push_back(obj);
}

void									GameObjectHandler::removeObject(GameObject *obj) {
	unsigned index = findIndex(obj);
	if (index < _allObjects.size()) _allObjects.erase(_allObjects.begin() + index);
}

void 									GameObjectHandler::clearAllObjects(void) {
	for (std::vector<GameObject*>::iterator pObj = _allObjects.begin(); pObj != _allObjects.end(); ++pObj)
		delete *pObj;
	_allObjects.clear();
}

void									GameObjectHandler::setObjectCanDraw(GameObject *obj, bool bCanDraw) {
	unsigned index = findIndex(obj);
	if (index < _allObjects.size()) _allObjects[index]->setCanDraw(bCanDraw);
}

void									GameObjectHandler::setAllObjectsCanDraw(bool bCanDraw) {
	for(GameObject* tmp : _allObjects) tmp->setCanDraw(bCanDraw);
}

void									GameObjectHandler::printAllObjects(void) {
	for(GameObject* tmp : _allObjects) tmp->draw();
}

// Output pverload for testing
std::ostream							&operator<<(std::ostream &o, GameObjectHandler const &i) {
	return o << "GameObjectHandler Info:" << &i << std::endl;
}
