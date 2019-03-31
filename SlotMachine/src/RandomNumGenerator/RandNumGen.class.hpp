#ifndef RAND_NUM_GEN_CLASS_HPP
	#define RAND_NUM_GEN_CLASS_HPP

	#include <iostream>
	#include <chrono>

	class RandNumGen {

		// Storing the last number generated
		unsigned	_min;
		unsigned	_max;


	public:

		// Constructors --
		RandNumGen(void);
		RandNumGen(unsigned min, unsigned max);
		~RandNumGen(void);

		// Getters --
		unsigned	getMin(void) const;
		unsigned	getMax(void) const;

		// Setters --
		void		setMin(unsigned min);
		void		setMax(unsigned max);

		// Helper Methods --
		unsigned	getNextRand(void);

	};

#endif
