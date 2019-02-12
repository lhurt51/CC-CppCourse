#ifndef PLAYER_CLASS_HPP
	#define PLAYER_CLASS_HPP

	#include <includes.hpp>

	class Player : public Actor {

		WINDOW					*_window;
		int							_input;
		bool						_bExitReq;
		static Vector2D	_spawnLoc;

	public:

		Player(WINDOW *window, char const sprite);
		Player(Player const &src);
		virtual ~Player(void);

		Player					&operator=(Player const &rhs);

		// Getters
		int							getUserInput(void) const;
		bool						getExitReq(void) const;

		// Setters
		static bool			setSpawnLoc(Vector2D spawnLoc);

		void						tick(void);

	private:

		void 						_checkPos(void);
		void						_handleUserInput(void);

	};

	// To print the player info
	std::ostream      &operator<<(std::ostream &o, Player const &i);

#endif
