#ifndef ACTOR_CLASS_HPP
	#define ACTOR_CLASS_HPP

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

	class Actor {

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

		// Static vector for all actors created
		static std::vector<Actor*>	_allActors;

	public:

		// Constructors --
		Actor(Vector2D<uint_fast32_t> pos, std::string const sprite);
		Actor(Actor const &src);
		virtual ~Actor(void);

		// Overload equals operator
		Actor						&operator=(Actor const &rhs);

		// Getters --
		int							getThisIndexInAllActors(void);
		bool						getCanDraw(void) const;
		bool						getCanClear(void) const;
		bool						getNeedsUpdate(void) const;
		Vector2D<uint_fast32_t>		getPos(void) const;
		std::string	const			getSprite(void) const;

		// Setters --
		void						setCanDraw(bool bCanDraw);
		void						setCanClear(void);
		void						resetNeedsUpdate(void);
		void 						setPos(Vector2D<uint_fast32_t> pos);
		void						setSprite(std::string sprite);

		// An abstract method for implemented classes
		virtual void				tick(void) = 0;

		// Actor Statics ------
		static std::vector<Actor*>	getAllActors(void);
		static void					removeActors(void);
		static void					tickAllActors(void);
		static void					printAllActors(void);
		static Actor*				getActor(unsigned index);
		static int					findActorIndex(Actor *actor);
		static void					addActor(Actor *actor);
		static void					removeActor(Actor *actor);
		static void					setAllActorsCanDraw(bool bCanDraw);
		static void					setActorCanDraw(unsigned index, bool bCanDraw);
		static void					setAllActorsCanClear();
		static void					setActorCanClear(unsigned index);
		static void					resetAllActorsNeedsUpdate();
		static void					resetActorNeedsUpdate(unsigned index);
		static bool					anyActorNeedsUpdate(void);

	};

	// To print the actor info
	std::ostream      &operator<<(std::ostream &o, Actor const &i);

#endif
