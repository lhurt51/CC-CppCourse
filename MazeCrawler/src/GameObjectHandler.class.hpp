#ifndef GAME_OBJECT_HANDLER_CLASS_HPP
	#define GAME_OBJECT_HANDLER_CLASS_HPP

	// All basic includes
	#include <includes.hpp>
	// For using vectors
	#include <vector>

	// Forward declaring classes
	template<typename T> class				Vector2D;
	class									GameObject;

	class GameObjectHandler {

	protected:

		// All objects created
		static std::vector<GameObject*> 	_allObjects;

	public:

		// Helper methods --
		static unsigned						findIndex(GameObject *obj);
		static GameObject*					findObject(unsigned index);
		static void							addObject(GameObject *obj);
		static void							removeObject(GameObject *obj);
		static void 						clearAllObjects(void);
		static void							setObjectCanDraw(GameObject *obj, bool bCanDraw);
		static void							setAllObjectsCanDraw(bool bCanDraw);
		static void							printAllObjects(void);

		// For a dirived class
		// virtual GameObject*				chooseObect(int type) = 0;

	};

	// To print the actor info
	std::ostream						&operator<<(std::ostream &o, GameObjectHandler const &i);

#endif
