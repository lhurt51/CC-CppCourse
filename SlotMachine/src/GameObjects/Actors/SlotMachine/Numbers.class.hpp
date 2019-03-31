#ifndef NUMBERS_CLASS_HPP
	#define NUMBERS_CLASS_HPP

	#include "../Actor.class.hpp"

	// Forward class definitions
	class						Timer;
	class						RandNumGen;

	class Numbers : public Actor {

		bool					_bRolling;
		unsigned				_curNum;
		double					_interval;
		Timer*					_timer;
		RandNumGen*				_randNumGen;

	public:

		// Constructors --
		Numbers(Vector2D<uint_fast32_t> pos);
		Numbers(Numbers const &src);
		~Numbers(void);

		// Overload operators --
		Numbers&				operator=(Numbers const &rhs);

		// Getters --
		unsigned				getCurNum(void) const;
		Timer*					getTimer(void) const;

		// Setters --
		void					stopRolling(void);
		void					incInterval(void);

		// Helper Methods --
		void					changeSprite(void);

		// Overloaded Public Actor Methods --
		void					tick(void);

	};

#endif
