#ifndef STATIC_GAME_OBJECT_CLASS_HPP
	#define STATIC_GAME_OBJECT_CLASS_HPP

	// All basic includes
	#include <includes.hpp>

	// Forward declaring classes
	template<typename T> class Vector2D;

	class StaticGameObject {

	protected:

		// Boolean to draw the sprite to the screen
		bool						_bCanDraw;
		// Vector 2D for a position
		Vector2D<uint_fast32_t>		_pos;
		// String for displaying the actor
		std::string const			_sprite;

	public:

		// Constructors --
		StaticGameObject(Vector2D<uint_fast32_t> pos, std::string const sprite);
		StaticGameObject(StaticGameObject const &src);
		virtual ~StaticGameObject(void);

		// Overload equals operator
		StaticGameObject			&operator=(StaticGameObject const &rhs);

		// Getters --
		bool						getCanDraw(void) const;
		Vector2D<uint_fast32_t>		getPos(void) const;
		std::string	const			getSprite(void) const;

		// Setters --
		void						setCanDraw(bool bCanDraw);
		virtual void 				setPos(Vector2D<uint_fast32_t> pos);

	};

	// To print the actor info
	std::ostream      &operator<<(std::ostream &o, StaticGameObject const &i);

#endif
