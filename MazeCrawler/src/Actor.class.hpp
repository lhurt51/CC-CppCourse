#ifndef ACTOR_CLASS_HPP
	#define ACTOR_CLASS_HPP

	// For using vectors
	#include "StaticGameObject.class.hpp"

	class Actor : public StaticGameObject {

	protected:

		// Boolean to see if the actor can be cleared
		bool						_bCanClear;
		// Boolean to see if the sprite should be updated
		bool						_bNeedsUpdate;

	public:

		// Constructors --
		Actor(Vector2D<uint_fast32_t> pos, std::string const sprite);
		Actor(Actor const &src);
		virtual ~Actor(void);

		// Overload equals operator
		Actor						&operator=(Actor const &rhs);

		// Getters --
		bool						getCanClear(void) const;
		bool						getNeedsUpdate(void) const;

		// Setters --
		void						setCanClear(void);
		void						setNeedsUpdate(void);

		// Override/Implement base functionality --
		void 						setPos(Vector2D<uint_fast32_t> pos);
		void						setSprite(std::string sprite);

		// An abstract method for implemented classes
		virtual void				tick(void) = 0;

	};

	// To print the actor info
	std::ostream      &operator<<(std::ostream &o, Actor const &i);

#endif
