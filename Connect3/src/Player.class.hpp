#ifndef PLAYER_CLASS_HPP
	#define PLAYER_CLASS_HPP

	#include "Actor.class.hpp"
	#include "Board.class.hpp"
	#include "GamePiece.class.hpp"

	class Player : public Actor {

		unsigned int const			_id;
		Board						*_board;
		int							_xDif;
		bool						_bExitReq;
		bool						_bSpawnPiece;
		bool						_updatePos;

	public:

		Player(Board *board, char const sprite);
		Player(Player const &src);
		virtual ~Player(void);

		Player						&operator=(Player const &rhs);

		// Getters
		int							getPlayerID(void) const;
		Board 						*getBoard(void) const;
		int							getXDif(void) const;
		bool						getExitReq(void) const;
		bool						getSpawnPiece(void) const;
		bool						getUpdatePos(void) const;

		// Setters
		bool						setBoard(Board* board);
		void						setXDif(int xDif);
		void						setUpdatePos(bool bShould);

		GamePiece					*createPiece(void);

		void						tick(void);

	protected:

		void 						_checkPos(void);

	private:

		bool 						_checkInput(int input);
		void						_handleUserInput(int input);

	};

	// To print the player info
	std::ostream      				&operator<<(std::ostream &o, Player const &i);

#endif
