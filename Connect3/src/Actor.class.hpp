#ifndef ACTOR_CLASS_HPP
	#define ACTOR_CLASS_HPP

	#include <ncurses.h>
	#include <typedefs.hpp>
	#include <includes.hpp>
	#include "Vector2D.class.hpp"

	class Actor {

	protected:

		bool				_bCanDraw;
		Vector2D			_pos;
		char const			_sprite;

	public:

		Actor(Vector2D pos, char const sprite);
		Actor(Actor const &src);
		virtual ~Actor(void);

		Actor					&operator=(Actor const &rhs);

		bool					getCanDraw(void) const;
		Vector2D				getPos(void) const;
		char					getSprite(void) const;

		void					setCanDraw(bool bCanDraw);
		bool 					setPos(Vector2D pos);

		bool					move(Vector2D dst);
		void					redraw(void);

		virtual void			tick(void) = 0;

	protected:

		virtual void			_checkPos(void) = 0;
		virtual void 			_draw(void) const;
		virtual void 			_clear(void) const;

	};

	// To print the actor info
	std::ostream      &operator<<(std::ostream &o, Actor const &i);

#endif
