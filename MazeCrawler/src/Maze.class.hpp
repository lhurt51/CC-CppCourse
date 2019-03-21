#ifndef MAZE_CLASS_HPP
	#define MAZE_CLASS_HPP

	// Includes for inheritance
	#include "Actor.class.hpp"

	class Maze : public Actor {

	public:

		Maze(Vector2D<uint_fast32_t> pos);
		Maze(Maze const &src);
		~Maze(void);

		Maze		&operator=(Maze const &rhs);

		// Actor abstract method implementation
		void		tick(void);

	};

#endif
