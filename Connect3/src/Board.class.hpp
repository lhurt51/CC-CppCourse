#ifndef BOARD_CLASS_HPP
	#define BOARD_CLASS_HPP

	#include <includes.hpp>
	#include "Vector2D.class.hpp"

	class Board {

		// A 2D char array acting as a board
		bool	_bCanUpdate;
		char	**_board;

	public:
		// Constructors
		Board(void);
		Board(Board const &src);
		~Board(void);

		// Overload operators
		Board		&operator=(Board const &rhs);

		// Getters
		bool		getBoardCanUpdate(void) const;
		char		**getBoard(void) const;

		// Setters
		void		initBoard(void);
		bool		addPieceToPoint(int row, int col, char c);

		// Misc. helper methods
		bool		isColFull(int col) const;
		bool		isColEmpty(int col) const;

		void		tick(Vector2D maxWinDem);

	private:

		void		_drawBoardToScreen(Vector2D maxWinDem) const;
	};

	// To print the board info
	std::ostream      &operator<<(std::ostream &o, Board const &i);

#endif
