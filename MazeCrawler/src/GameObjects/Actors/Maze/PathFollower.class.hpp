#ifndef PATH_FOLLOWER_CLASS_HPP
	#define PATH_FOLLOWER_CLASS_HPP

	#include <vector>
	// Includes for inheritance
	#include "GameObjects/Actors/Actor.class.hpp"

	class PathFollower : public Actor {

		std::vector<Vector2D<uint_fast32_t>> 	_path;

	public:

		PathFollower(Vector2D<uint_fast32_t> pos);
		PathFollower(PathFollower const &src);
		~PathFollower(void);

		PathFollower							&operator=(PathFollower const &rhs);

		// Getters --
		std::vector<Vector2D<uint_fast32_t>>	getPath(void) const;

		// Helper methods --
		bool									followPath(unsigned index);

		// Actor override methods --
		virtual void 							draw(void) override;

		// Actor abstract method implementation
		void									tick(void) override;

	};

#endif
