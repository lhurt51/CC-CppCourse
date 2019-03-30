#ifndef INPUT_CLASS_HPP
	#define INPUT_CLASS_HPP

	#include <includes.hpp>
	#include "Actor.class.hpp"

	class Input : public Actor {

		// Checks if the user is typing their input
		bool				_bIsTyping;
		bool				_bIsChar;

	public:

		// Constructors --
		Input(Vector2D<uint_fast32_t> pos);
		Input(Input const &src);
		~Input(void);

		// Overload operators --
		Input&				operator=(Input const &rhs);

		// Getters --
		bool				getIsTyping(void) const;
		bool				getIsChar(void) const;

		// Setters --
		void				setIsTyping(void);
		void				addInputToString(int input);

		// Helper Methods
		void				finnishInput(void);

		// Overloaded Public Actor Methods --
		void				tick(void) override;

	private:
		// Private helpers
		bool				_is_digits(const std::string &str);
		bool				_is_alphas(const std::string &str);

	};

#endif
