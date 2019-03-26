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
#include "GameObjects/Actors/Actor.class.hpp"
#include "ActorHandler.class.hpp"

unsigned								ActorHandler::findActorIndex(Actor *obj) {
	unsigned	start = 0;
	Actor*		myActor;

	for(GameObject* tmp : _allObjects) {
		if ((myActor = dynamic_cast<Actor*>(tmp))) {
			if (myActor == obj)
				return start;
		}
		start++;
	}
	return start + 1;
}

Actor*									ActorHandler::findActor(unsigned index) {
	Actor*		myActor;

	if (index < _allObjects.size() && (myActor = dynamic_cast<Actor*>(_allObjects[index])))
		return myActor;
	return nullptr;
}

void									ActorHandler::setActorCanClear(Actor *obj) {
	Actor*		myActor;
	unsigned index = findActorIndex(obj);

	if (index < _allObjects.size() && (myActor = dynamic_cast<Actor*>(_allObjects[index])))
		myActor->setCanClear();
}

void									ActorHandler::setAllActorsCanClear(void) {
	Actor*		myActor;

	for(GameObject* tmp : _allObjects) {
		if ((myActor = dynamic_cast<Actor*>(tmp)))
			myActor->setCanClear();
	}
}

void									ActorHandler::setActorNeedsUpdate(Actor *obj) {
	Actor*		myActor;
	unsigned index = findActorIndex(obj);

	if (index < _allObjects.size() && (myActor = dynamic_cast<Actor*>(_allObjects[index])))
		myActor->setNeedsUpdate();
}

void									ActorHandler::setAllActorsNeedsUpdate(void) {
	Actor*		myActor;

	for(GameObject* tmp : _allObjects) {
		if ((myActor = dynamic_cast<Actor*>(tmp)))
			myActor->setNeedsUpdate();
	}
}

bool									ActorHandler::anyActorNeedsUpdate(void) {
	Actor*		myActor;

	for(GameObject* tmp : _allObjects) {
		if ((myActor = dynamic_cast<Actor*>(tmp)) && myActor->getNeedsUpdate())
			return true;
	}
	return false;
}

void									ActorHandler::tickAllActors(void) {
	Actor*		myActor;

	for(GameObject* tmp : _allObjects) {
		if ((myActor = dynamic_cast<Actor*>(tmp))) {
			myActor->tick();
		}
	}
}

// Output pverload for testing
std::ostream							&operator<<(std::ostream &o, ActorHandler const &i) {
	return o << "ActorHandler Info:" << &i << std::endl;
}
