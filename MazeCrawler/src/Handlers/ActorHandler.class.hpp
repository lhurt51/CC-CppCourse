#ifndef ACTOR_HANDLER_CLASS_HPP
	#define ACTOR_HANDLER_CLASS_HPP

	#include "GameObjectHandler.class.hpp"

	// Forward declaring classes
	class									Actor;

	class ActorHandler : public GameObjectHandler {

	public:

		// Helper methods --
		static unsigned						findActorIndex(Actor *obj);
		static Actor*						findActor(unsigned index);
		static void							setActorCanClear(Actor *obj);
		static void							setAllActorsCanClear(void);
		static void							setActorNeedsUpdate(Actor *obj);
		static void							setAllActorsNeedsUpdate(void);
		static bool							anyActorNeedsUpdate(void);
		static void							tickAllActors(void);

		// For a dirived class
		// virtual Actor*					chooseActor(int type) = 0;

	};

	// To print the actor info
	std::ostream						&operator<<(std::ostream &o, ActorHandler const &i);

#endif
