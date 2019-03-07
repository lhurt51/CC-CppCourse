#ifndef ACTOR_CLASS_HPP
	#define ACTOR_CLASS_HPP

	#include <includes.hpp>
	#include <vector>

	template<typename T>
    class Vector2D;

	class Actor {

	protected:

		bool						_bCanDraw;
		bool						_bCanClear;
		Vector2D<uint_fast32_t>		_pos;
		std::string const			&_sprite;

		static std::vector<Actor*>	_allActors;

	public:

		Actor(Vector2D<uint_fast32_t> pos, std::string const &sprite);
		Actor(Actor const &src);
		virtual ~Actor(void);

		Actor						&operator=(Actor const &rhs);

		int							getAllActorsIndex(void);
		bool						getCanDraw(void) const;
		bool						getCanClear(void) const;
		Vector2D<uint_fast32_t>		getPos(void) const;
		std::string	const			&getSprite(void) const;

		void						setCanDraw(bool bCanDraw);
		void						setCanClear(bool bCanDraw);
		void 						setPos(Vector2D<uint_fast32_t> pos);

		bool						move(Vector2D<uint_fast32_t> dst);

		virtual void				tick(void) = 0;

		// Actor Statics ------
		static std::vector<Actor*>	getAllActors(void);
		static void					removeActors(void);
		static void					tickAllActors(void);
		static void					printAllActors(void);
		static Actor*				getActor(unsigned index);
		static int					findActorIndex(Actor &actor);
		static void					addActor(Actor *actor);
		static void					removeActor(Actor &actor);
		static void					setAllActorsCanDraw(bool bCanDraw);
		static void					setActorCanDraw(unsigned index, bool bCanDraw);
		static void					setActorCanClear(unsigned index, bool bCanClear);

	};

	// To print the actor info
	std::ostream      &operator<<(std::ostream &o, Actor const &i);

#endif
