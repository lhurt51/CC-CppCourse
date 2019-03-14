#ifndef INPUT_CLASS_HPP
	#define INPUT_CLASS_HPP

	#include <includes.hpp>
	#include "Actor.class.hpp"
	#include "GameState.class.hpp"

	class Input : public Actor {

		GameState&			_gameState;
		// Checks if the user is typing their input
		bool				_bIsTyping;
		bool				_bIsChar;

	public:

		// Constructors --
		Input(GameState &gameState, Vector2D<uint_fast32_t> pos);
		Input(Input const &src);
		~Input(void);

		// Overload operators --
		Input&				operator=(Input const &rhs);

		// Getters --
		GameState			&getGameState(void) const;
		bool				getIsTyping(void) const;
		bool				getIsChar(void) const;

		// Setters --
		void				setIsTyping(void);
		void				addInputToString(int input);

		// Helper Methods
		void				finnishInput(void);

		// Overloaded Public Actor Methods --
		void				tick(void);

	private:
		// Private helpers
		bool				_is_digits(const std::string &str);
		bool				_is_alphas(const std::string &str);

	};

#endif
