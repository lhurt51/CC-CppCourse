#ifndef PLAYER_CLASS_HPP
	#define PLAYER_CLASS_HPP

	#include "Actor.class.hpp"

	class Player : public Actor {

		// Checks if the user can input
		bool				_bCanInput;
		// Checks if the user wants to exit the program
		bool				_bExitReq;
		// Checks if the user is typing their input
		bool				_bIsTyping;

	public:

		// Constructors --
		Player(void);
		Player(Player const &src);
		virtual ~Player(void);

		// Overload operators --
		Player&				operator=(Player const &rhs);

		// Getters --
		bool				getCanInput(void) const;
		bool				getExitReq(void) const;
		bool				getIsTyping(void) const;

		// Setters --
		void				setCanInput(bool bCanInput);
		void				setExitReq(bool bExitReq);
		void				setIsTyping(bool bIsTyping);

		// Overloaded Public Actor Methods --
		void				tick(void);

	protected:

		// Overloaded Protected Actor Methods --
		void				_checkPos(void);

	private:

		// Handle the users input
		void				_handleUserInput(int input);

	};

#endif
