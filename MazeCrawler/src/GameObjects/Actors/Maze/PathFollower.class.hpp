#ifndef PATH_FOLLOWER_CLASS_HPP
	#define PATH_FOLLOWER_CLASS_HPP

	#include <vector>
	// Includes for inheritance
	#include "GameObjects/Actors/Actor.class.hpp"
	// Forward declaring classes
	class										Maze;
	class										AsynFuncTimer;

	class PathFollower : public Actor {

		Maze&									_maze;
		AsynFuncTimer*							_timer;
		unsigned 								_index;
		std::vector<Vector2D<uint_fast32_t>> 	_path;

	public:

		PathFollower(Maze& maze, std::vector<Vector2D<uint_fast32_t>> path);
		PathFollower(PathFollower const &src);
		~PathFollower(void);

		PathFollower							&operator=(PathFollower const &rhs);

		// Getters --
		Maze&									getMaze(void) const;
		AsynFuncTimer*							getTimer(void) const;
		unsigned								getIndex(void) const;
		std::vector<Vector2D<uint_fast32_t>>	getPath(void) const;

		// Helper methods --
		void									followPath(void);

		// Actor override methods --
		virtual void 							draw(void) override;

		// Actor abstract method implementation
		void									tick(void) override;

	};

#endif
