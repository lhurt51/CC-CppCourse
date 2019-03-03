#ifndef ACTOR_CLASS_HPP
	#define ACTOR_CLASS_HPP

	#include <ncurses.h>
	#include <typedefs.hpp>
	#include <includes.hpp>
	#include "Vector2D.class.hpp"

	class Actor {

		unsigned int const			_id;

	protected:

		bool						_bCanDraw;
		bool						_bCanClear;
		Vector2D<uint_fast32_t>		_pos;
		char const					_sprite;

	public:
		
		static unsigned int			actorCount;

		Actor(Vector2D pos, char const sprite);
		Actor(Actor const &src);
		virtual ~Actor(void);

		Actor						&operator=(Actor const &rhs);

		int							getId(void) const;
		bool						getCanDraw(void) const;
		bool						getCanClear(void) const;
		Vector2D					getPos(void) const;
		char						getSprite(void) const;

		void						setCanDraw(bool bCanDraw);
		void						setCanClear(bool bCanDraw);
		void 						setPos(Vector2D pos);

		bool						move(Vector2D dst);
		void						redraw(void);

		virtual void				tick(void) = 0;

	protected:

		virtual void				_checkPos(void) = 0;
		virtual void 				_draw(void) const;

	};

	// To print the actor info
	std::ostream      &operator<<(std::ostream &o, Actor const &i);

#endif
