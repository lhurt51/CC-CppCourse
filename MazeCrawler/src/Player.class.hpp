#ifndef PLAYER_CLASS_HPP
	#define PLAYER_CLASS_HPP

	#include <includes.hpp>
	#include "Actor.class.hpp"

	class Player : public Actor {

		// Checks if the user is typing their input
		bool				_bIsTyping;
		// Checks if the user wants to move right
		bool				_mRightPressed;
		// Checks if the user wants to move left
		bool				_mLeftPressed;

	public:

		// Constructors --
		Player(void);
		Player(Player const &src);
		~Player(void);

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

		// Helper Methods
		bool				move(Vector2D<uint_fast32_t> dst);

		// Overloaded Public Actor Methods --
		void				tick(void);

	};

#endif
