#ifndef ASYN_FUNC_TIMER_CLASS_HPP
	#define ASYN_FUNC_TIMER_CLASS_HPP

	#include <iostream>
	#include <chrono>
	#include <functional>
	#include <thread>

	class AsynFuncTimer {

		// Function to be exec
		std::function<void(void)>	_func;
		// Timer interval in millisecs
		long						_interval;

		// Thread timer is running into
		std::thread					_thread;
		// Status if timer is running
		bool						_running = false;

	public:

		// Constructors --
		AsynFuncTimer(std::function<void(void)> func, const long &interval);
		~AsynFuncTimer(void);

		// Getters --
		bool						isRunning(void) const;
		long						getInterval(void) const;

		// Setters --
		AsynFuncTimer*				setFunc(std::function<void(void)> func);
		AsynFuncTimer*				setInterval(const long &interval);

		// Helper Functions --
		void						start(void);
		void						stop(void);
		void						reset(void);

	};

#endif
