#ifndef GAME_PIECE_CLASS_HPP
	#define GAME_PIECE_CLASS_HPP

	#include "Actor.class.hpp"
	#include "Board.class.hpp"

	class GamePiece : public Actor {

		// To see if the piece can be deleted
		bool			_bCanClear;
		// Found a spot on the board
		bool			_bFoundPos;
		// The starting position for the animation
		Vector2D const	_startPos;
		// The board pointer to check the board
		Board			*_board;

	public:

		// Constructors
		GamePiece(Board *board, char const sprite, Vector2D const pos);
		GamePiece(GamePiece const &src);
		~GamePiece(void);

		// Overload operators
		GamePiece		&operator=(GamePiece const &rhs);

		// Getters
		bool			getCanClear(void) const;
		bool			getFoundPos(void) const;
		Vector2D		getStartPos(void) const;
		Board			*getBoard(void) const;

		//Setters
		bool			setStartPos(Vector2D const vec);

		// Actor abstract functions --
		void			tick(void);

	protected:

		void 			_checkPos(void);
		
		// Actor method overload
		void			_clear(void) const;

	};

	// To print the player info
	std::ostream      	&operator<<(std::ostream &o, GamePiece const &i);

#endif
