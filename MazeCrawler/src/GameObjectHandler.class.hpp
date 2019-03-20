#ifndef GAME_OBJECT_HANDLER_CLASS_HPP
	#define GAME_OBJECT_HANDLER_CLASS_HPP

	// All basic includes
	#include <includes.hpp>
	// For using vectors
	#include <vector>

	// Forward declaring classes
	template<typename T> class			Vector2D;
	class								GameObject;

	class GameObjectHandler {

		// All objects created
		std::vector<GameObject*> 		_allObjects;

	public:

		// Constructors --
		GameObjectHandler(void);
		GameObjectHandler(GameObjectHandler const &src);
		virtual ~GameObjectHandler(void);

		// Overload equals operator --
		GameObjectHandler				&operator=(GameObjectHandler const &rhs);

		// Getters --
		std::vector<GameObject*>		getAllObjects(void) const;

		// Helper methods --
		unsigned						findIndex(GameObject *obj);
		GameObject*						findObject(unsigned index);
		void							addObject(GameObject *obj);
		void							removeObject(GameObject *obj);
		void							setObjectCanDraw(GameObject *obj, bool bCanDraw);
		void							setAllObjectsCanDraw(bool bCanDraw);
		void							printAllObjects(void);

		// For a dirived class
		// virtual GameObject*				chooseObect(int type) = 0;

	};

	// To print the actor info
	std::ostream						&operator<<(std::ostream &o, GameObjectHandler const &i);

#endif
