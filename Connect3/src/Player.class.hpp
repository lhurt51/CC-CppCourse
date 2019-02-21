#ifndef PLAYER_CLASS_HPP
	#define PLAYER_CLASS_HPP

	#include "Actor.class.hpp"
	#include "Board.class.hpp"
	#include "GamePiece.class.hpp"

	class Player : public Actor {

		// Storing a ref to the board
		Board						*_board;
		// The difference in x for the actors pos
		int							_xDif;
		// Is it this players turn
		bool						_bIsTurn;
		// Prevent this player from spawning or moving
		bool						_bCanInput;
		// Did this player request an exit
		bool						_bExitReq;
		// Did this player request a spawn piece
		bool						_bSpawnPiece;

	public:

		// Constructors --
		Player(Board *board, char const sprite);
		Player(Player const &src);
		virtual ~Player(void);

		// Overload operators --
		Player						&operator=(Player const &rhs);

		// Getters --
		Board 						*getBoard(void) const;
		int							getXDif(void) const;
		bool						getIsTurn(void) const;
		bool						getCanInput(void) const;
		bool						getExitReq(void) const;
		bool						getSpawnPiece(void) const;

		// Setters --
		void						setXDif(int xDif);
		void						setCanInput(bool bCanInput);
		void						setIsTurn(bool bIsTurn);

		// Helper methods --
		void						shouldUpdate(void);
		GamePiece					*createPiece(void);

		// Virtual override functions --
		void						tick(void);

	protected:

		void 						_checkPos(void);

	private:

		// Private functions --
		void						_handleUserInput(int input);

	};

	// To print the player info
	std::ostream      				&operator<<(std::ostream &o, Player const &i);

#endif
