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
