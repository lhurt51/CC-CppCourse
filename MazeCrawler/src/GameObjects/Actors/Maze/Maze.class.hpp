#ifndef MAZE_CLASS_HPP
	#define MAZE_CLASS_HPP

	// Includes for inheritance
	#include "GameObjects/Actors/Actor.class.hpp"

	class Maze : public Actor {

		bool					_bFoundPath;
		Vector2D<uint_fast32_t>	_spriteDim;

	public:

		Maze(Vector2D<uint_fast32_t> pos);
		Maze(Maze const &src);
		~Maze(void);

		Maze					&operator=(Maze const &rhs);

		// Getters --
		bool					getFoundPath(void) const;
		Vector2D<uint_fast32_t>	getSpriteDim(void) const;

		// Setters --
		void					setFoundPath(void);
		void					setSpriteDim(void);

		// Helper methods --
		bool					findPath(std::string sprite, Vector2D<int> startingPos);

		// Actor abstract method implementation
		void					tick(void) override;

	};

#endif
