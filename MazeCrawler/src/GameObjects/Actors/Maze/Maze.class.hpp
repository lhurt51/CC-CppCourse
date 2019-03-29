#ifndef MAZE_CLASS_HPP
	#define MAZE_CLASS_HPP

	#include <vector>

	// Includes for inheritance
	#include "GameObjects/Actors/Actor.class.hpp"
	class						PathFollower;

	class Maze : public Actor {

		bool									_bFoundPath;
		Vector2D<uint_fast32_t>					_spriteDim;
		PathFollower*							_follower;
		std::vector<Vector2D<uint_fast32_t>> 	_path;

	public:

		Maze(Vector2D<uint_fast32_t> pos);
		Maze(Maze const &src);
		~Maze(void);

		Maze									&operator=(Maze const &rhs);

		// Getters --
		bool									getFoundPath(void) const;
		Vector2D<uint_fast32_t>					getSpriteDim(void) const;

		// Setters --
		void									setFoundPath(void);
		void									setSpriteDim(void);

		// Actor override methods --
		virtual void							setPos(Vector2D<uint_fast32_t> pos) override;

		// Helper methods --
		Vector2D<uint_fast32_t> 				convToWorldCoords(Vector2D<uint_fast32_t> boardCoords);
		bool									findPath(std::string sprite, Vector2D<int> startingPos);
		void 									addCharToMaze(Vector2D<uint_fast32_t> boardCoords, char c);

		// Actor abstract method implementation
		void									tick(void) override;

	private:

		void									_initFollower(void);
		void									_deleteFollower(void);

	};

#endif
