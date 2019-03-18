#ifndef STATIC_GAME_OBJECT_HANDLER_CLASS_HPP
	#define STATIC_GAME_OBJECT_HANDLER_CLASS_HPP

	// All basic includes
	#include <includes.hpp>
	// For using vectors
	#include <vector>

	// Forward declaring classes
	template<typename T> class			Vector2D;
	class								StaticGameObject;

	class StaticGameObjectHandler {

		// All objects created
		std::vector<StaticGameObject*> 	_allObjects;

	public:

		// Constructors --
		StaticGameObjectHandler(void);
		StaticGameObjectHandler(StaticGameObjectHandler const &src);
		virtual ~StaticGameObjectHandler(void);

		// Overload equals operator --
		StaticGameObjectHandler			&operator=(StaticGameObjectHandler const &rhs);

		// Getters --
		std::vector<StaticGameObject*>	getAllObjects(void) const;

		// Helper methods --
		int								findObject(StaticGameObject *obj);
		void							addObject(StaticGameObject *obj);
		void							removeObject(StaticGameObject *obj);
		void							printAllObjects(void);

	};

	// To print the actor info
	std::ostream						&operator<<(std::ostream &o, StaticGameObjectHandler const &i);

#endif
