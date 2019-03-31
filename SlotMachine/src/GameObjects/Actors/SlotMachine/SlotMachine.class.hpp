#ifndef SLOT_MACHINE_CLASS_HPP
	#define SLOT_MACHINE_CLASS_HPP

	#include <vector>
	#include "GameObjects/Actors/Actor.class.hpp"

	class							Timer;
	class							Numbers;

	class SlotMachine : public Actor {

		double						_interval;
		Timer*						_timer;
		std::vector<Numbers*>		_numbers;
		// float						_bet;
		// float						_winnings;

	public:

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

		// Overloaded Public Actor Methods --
		void						tick(void);

	private:

		void						deleteTimer(void);
		void						deleteNumbers(void);

	};

#endif
