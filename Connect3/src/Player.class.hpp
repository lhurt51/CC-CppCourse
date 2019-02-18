#ifndef PLAYER_CLASS_HPP
	#define PLAYER_CLASS_HPP

	#include "Actor.class.hpp"
	#include "Board.class.hpp"

	class Player : public Actor {

		unsigned int const			_id;
		int							_xDif;
		bool						_bExitReq;
		bool						_updatePos;
		Board						*_board;

	public:

		Player(Board *board, char const sprite);
		Player(Player const &src);
		virtual ~Player(void);

		Player						&operator=(Player const &rhs);

		// Getters
		int							getPlayerID(void) const;
		int							getXDif(void) const;
		bool						getExitReq(void) const;
		bool						getUpdatePos(void) const;
		Board						*getBoard(void) const;

		// Setters
		void						setXDif(int xDif);
		void						setUpdatePos(bool bShould);
		bool						setBoard(Board* board);

		void						tick(void);

	protected:

		void 						_checkPos(void);

	private:

		bool 						_checkInput(int input);
		void						_handleUserInput(int input);

	};

	// To print the player info
	std::ostream      &operator<<(std::ostream &o, Player const &i);

#endif
