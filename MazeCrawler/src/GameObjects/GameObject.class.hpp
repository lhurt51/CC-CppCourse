#ifndef GAME_OBJECT_CLASS_HPP
	#define GAME_OBJECT_CLASS_HPP

	// All basic includes
	#include <includes.hpp>

	// Forward declaring classes
	template<typename T> class Vector2D;

	class GameObject {

	protected:

		// Boolean to draw the sprite to the screen
		bool						_bCanDraw;
		// Vector 2D for a position
		Vector2D<uint_fast32_t>		_pos;
		// String for displaying the actor
		std::string const			_sprite;

	public:

		// Constructors --
		GameObject(Vector2D<uint_fast32_t> pos, std::string const sprite);
		GameObject(GameObject const &src);
		virtual ~GameObject(void);

		// Overload equals operator
		GameObject			&operator=(GameObject const &rhs);

		// Getters --
		bool						getCanDraw(void) const;
		Vector2D<uint_fast32_t>		getPos(void) const;
		std::string	const			getSprite(void) const;

		// Setters --
		void						setCanDraw(bool bCanDraw);
		virtual void 				setPos(Vector2D<uint_fast32_t> pos);

		// Helper methods --
		virtual void 				draw(void);

	};

	// To print the actor info
	std::ostream      &operator<<(std::ostream &o, GameObject const &i);

#endif
