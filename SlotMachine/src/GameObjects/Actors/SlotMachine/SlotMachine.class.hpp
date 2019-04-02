#ifndef SLOT_MACHINE_CLASS_HPP
	#define SLOT_MACHINE_CLASS_HPP

	#include <vector>
	#include "GameObjects/Actors/Actor.class.hpp"

	class							Timer;
	class							Numbers;
	class							GameObject;

	class SlotMachine : public Actor {

		GameObject*					_gameOverDsp;
		unsigned					_rollIndex;
		double						_interval;
		Timer*						_timer;
		std::vector<Numbers*>		_numbers;
		float						_bet;

	public:

		static float				winnings;

		// Constructors --
		SlotMachine(void);
		SlotMachine(SlotMachine const &src);
		~SlotMachine(void);

		// Overload operators --
		SlotMachine&				operator=(SlotMachine const &rhs);

		// Getters --
		Timer*						getTimer(void) const;
		std::vector<Numbers*>		getNumbers(void) const;

		// Setters --
		void						setTimer(void);
		void						setNumbers(void);

		// Helper Methods
		void						startRoll(void);
		void						endRoll(void);

		// Overloaded Public Actor Methods --
		void						tick(void);

	private:

		void						deleteTimer(void);
		void						deleteNumbers(void);

	};

#endif
