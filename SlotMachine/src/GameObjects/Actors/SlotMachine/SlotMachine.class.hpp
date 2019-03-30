#ifndef SLOT_MACHINE_CLASS_HPP
	#define SLOT_MACHINE_CLASS_HPP

	#include "GameObjects/Actors/Actor.class.hpp"

	class SlotMachine : public Actor {



	public:

		// Constructors --
		SlotMachine(void);
		SlotMachine(SlotMachine const &src);
		~SlotMachine(void);

		// Overload operators --
		SlotMachine&				operator=(SlotMachine const &rhs);

		// Getters --

		// Setters --

		// Helper Methods

		// Overloaded Public Actor Methods --
		void				tick(void);

	};

#endif
