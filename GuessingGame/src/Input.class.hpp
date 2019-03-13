#ifndef INPUT_CLASS_HPP
	#define INPUT_CLASS_HPP

	#include <includes.hpp>
	#include "Actor.class.hpp"

	class Input : public Actor {

		// Checks if the user is typing their input
		bool				_bIsTyping;
		// Stores the players input
		std::string			_playerInput;

	public:

		// Constructors --
		Input(Vector2D<uint_fast32_t> pos);
		Input(Input const &src);
		~Input(void);

		// Overload operators --
		Input&				operator=(Input const &rhs);

		// Getters --
		bool				getIsTyping(void) const;
		std::string			getPlayerInput(void) const;

		// Setters --
		void				addInputToString(int input);


		// Helper Methods


		// Overloaded Public Actor Methods --
		void				tick(void);

	};

#endif
