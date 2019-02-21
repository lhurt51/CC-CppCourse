#ifndef GAME_PIECE_CLASS_HPP
	#define GAME_PIECE_CLASS_HPP

	#include "Actor.class.hpp"
	#include "Board.class.hpp"

	class GamePiece : public Actor {

		bool			_bCanClear;
		Vector2D const	_startPos;
		Board			*_board;

	public:

		GamePiece(Board *board, char const sprite, Vector2D const pos);
		GamePiece(GamePiece const &src);
		~GamePiece(void);

		GamePiece		&operator=(GamePiece const &rhs);

		// Getters
		bool			getCanClear(void) const;
		Vector2D		getStartPos(void) const;
		Board			*getBoard(void) const;

		//Setters
		bool			setStartPos(Vector2D const vec);

		void			tick(void);

	protected:

		void 			_checkPos(void);
		void			_clear(void) const;

	};

	// To print the player info
	std::ostream      	&operator<<(std::ostream &o, GamePiece const &i);

#endif
