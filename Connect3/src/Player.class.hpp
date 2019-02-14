#ifndef PLAYER_CLASS_HPP
	#define PLAYER_CLASS_HPP

	#include <includes.hpp>
	#include "Actor.class.hpp"

	class Player : public Actor {

		unsigned int				_id;
		WINDOW						*_window;
		int							_input;
		bool						_bExitReq;
		static Vector2D	_spawnLoc;

	public:

		Player(WINDOW *window, char const sprite);
		Player(Player const &src);
		virtual ~Player(void);

		Player						&operator=(Player const &rhs);

		// Getters
		int							getPlayerID(void) const;
		int							getUserInput(void) const;
		bool						getExitReq(void) const;

		// Setters
		static bool			setSpawnLoc(Vector2D spawnLoc);

		void						tick(void);

	private:

		void 						_checkPos(void);
		bool 						_checkInput(void);
		void						_handleUserInput(void);

	};

	// To print the player info
	std::ostream      &operator<<(std::ostream &o, Player const &i);

#endif
