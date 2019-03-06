#ifndef ACTOR_CLASS_HPP
	#define ACTOR_CLASS_HPP

	#include <typedefs.hpp>
	#include <includes.hpp>
	#include "Vector2D.class.hpp"

	class Actor {

		unsigned int const			_id;

	protected:

		bool						_bCanDraw;
		bool						_bCanClear;
		Vector2D<uint_fast32_t>		_pos;
		std::string const			&_sprite;

	public:

		Actor(Vector2D<uint_fast32_t> pos, std::string const &sprite);
		Actor(Actor const &src);
		virtual ~Actor(void);

		Actor						&operator=(Actor const &rhs);

		int							getId(void) const;
		bool						getCanDraw(void) const;
		bool						getCanClear(void) const;
		Vector2D<uint_fast32_t>		getPos(void) const;
		std::string	const			&getSprite(void) const;

		void						setCanDraw(bool bCanDraw);
		void						setCanClear(bool bCanDraw);
		void 						setPos(Vector2D<uint_fast32_t> pos);

		bool						move(Vector2D<uint_fast32_t> dst);

		virtual void				tick(float deltaTime) = 0;

		// Actor Statics ------
	protected:

		static unsigned int			_actorCount;

	public:

		static std::vector<Actor*>	allActors;

	};

	// To print the actor info
	std::ostream      &operator<<(std::ostream &o, Actor const &i);

#endif
