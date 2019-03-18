#ifndef STATIC_RUN_TIME_COMPONENT_CLASS_HPP
	#define STATIC_RUN_TIME_COMPONENT_CLASS_HPP

	// All basic includes
	#include <includes.hpp>
	// For using vectors
	#include <vector>

	/********************************\
	 * WANT TO ADD BASE DISPLAY		*
	 * CLASS WITH DISPLAY HANDLER	*
	 * THEN ACTORS WITH ACTOR		*
	 * HANDLERS						*
	\********************************/

	// Forward declaring classes
	template<typename T> class Vector2D;

	class StaticRunTimeComponent {

	protected:

		// Boolean to draw the sprite to the screen
		bool						_bCanDraw;
		// Boolean to see if the actor can be cleared
		bool						_bCanClear;
		// Boolean to see if the sprite should be updated
		bool						_bNeedsUpdate;
		// Vector 2D for a position
		Vector2D<uint_fast32_t>		_pos;
		// String for displaying the actor
		std::string const			_sprite;

	public:

		// Constructors --
		StaticRunTimeComponent(Vector2D<uint_fast32_t> pos, std::string const sprite);
		StaticRunTimeComponent(StaticRunTimeComponent const &src);
		virtual ~StaticRunTimeComponent(void);

		// Overload equals operator
		StaticRunTimeComponent		&operator=(StaticRunTimeComponent const &rhs);

		// Getters --
		int							getThisIndexInAllStaticRunTimeComponents(void);
		bool						getCanDraw(void) const;
		bool						getCanClear(void) const;
		bool						getNeedsUpdate(void) const;
		Vector2D<uint_fast32_t>		getPos(void) const;
		std::string	const			getSprite(void) const;

		// Setters --
		void						setCanDraw(bool bCanDraw);
		void						setCanClear(void);
		void						setNeedsUpdate(void);
		void 						setPos(Vector2D<uint_fast32_t> pos);
		void						setSprite(std::string sprite);

		// An abstract method for implemented classes
		virtual void				tick(void) = 0;
	};

	// To print the actor info
	std::ostream      &operator<<(std::ostream &o, StaticRunTimeComponent const &i);

#endif
