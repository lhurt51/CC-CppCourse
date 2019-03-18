#ifndef TIMER_CLASS_HPP
	#define TIMER_CLASS_HPP

	#include <includes.hpp>
	#include <chrono>

	class Timer {

		// A reference of the clock
		typedef std::chrono::high_resolution_clock _clock;
		// A reference of the seconds
		typedef std::chrono::duration<double, std::ratio<1>> _second;
		// A reference of the starting time
		std::chrono::time_point<_clock> _beg;

	public:

		// Constructors --
		Timer(void);

		// Helper Functions --
		double		elapsed(void) const;
		void		reset(void);

	};

#endif
