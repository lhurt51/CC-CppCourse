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

#include "Vector2D.class.hpp"
#include "GameObjects/GameObject.class.hpp"
#include "GameObjectHandler.class.hpp"

std::vector<GameObject*> 				GameObjectHandler::_allObjects;

unsigned								GameObjectHandler::findIndex(GameObject *obj) {
	unsigned start = 0;

	for(GameObject* tmp : _allObjects) {
		if (tmp == obj) return start;
		start++;
	}
	return start + 1;
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
