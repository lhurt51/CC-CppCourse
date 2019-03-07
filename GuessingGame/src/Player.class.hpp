#ifndef PLAYER_CLASS_HPP
	#define PLAYER_CLASS_HPP

	#include <includes.hpp>
	#include "Actor.class.hpp"

	class Player : public Actor {

		// Checks if the user is typing their input
		bool				_bIsTyping;
		bool				_mRightPressed;
		bool				_mLeftPressed;

	public:

		// Constructors --
		Player(void);
		Player(Player const &src);
		virtual ~Player(void);

		// Overload operators --
		Player&				operator=(Player const &rhs);

		// Getters --
		bool				getIsTyping(void) const;
		bool				getPressingRight(void) const;
		bool				getPressingLeft(void) const;

		// Setters --
		void				startTyping(void);
		void				stopTyping(void);
		void				moveRight(void);
		void				stopRight(void);
		void				moveLeft(void);
		void				stopLeft(void);

		// Overloaded Public Actor Methods --
		void				tick(void);

	};

#endif
