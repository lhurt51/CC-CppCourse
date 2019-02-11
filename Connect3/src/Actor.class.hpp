#ifndef ACTOR_CLASS_HPP
	#define ACTOR_CLASS_HPP

	#include <includes.hpp>
	#include "Vector2D.class.hpp"

	class Actor {

	protected:

		Vector2D		_pos;
		char const		_sprite;
		bool			_bCollided;

	public:

		Actor(Vector2D pos, char const sprite);
		Actor(Actor const &src);
		virtual ~Actor(void);

		Actor			&operator=(Actor const &rhs);

		Vector2D		getPos(void) const;
		char			getSprite(void) const;
		bool			getBCollided(void) const;

		bool 			setPos(Vector2D pos);

		bool			bDoesCollide(Actor &src);
		bool			move(Vector2D dst);
		void 			draw(void);
		void 			clear(void);

		virtual void	tick(void) = 0;

	protected:

		virtual void	_hasCollided(void);
	};

	// To print the actor info
	std::ostream      &operator<<(std::ostream &o, Actor const &i);

#endif
