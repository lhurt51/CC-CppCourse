#ifndef BOARD_CLASS_HPP
	#define BOARD_CLASS_HPP

	#include <includes.hpp>
	#include "Vector2D.class.hpp"

	class Board {
		char	**_board;

	public:
		// Constructors
		Board(void);
		Board(Board const &src);
		~Board(void);

		// Overload operators
		Board		&operator=(Board const &rhs);

		// Getters
		char		**getBoard(void) const;
		bool		getBoardCanUpdate(void) const;

		// Setters
		void		initBoard(void);
		bool		addPieceToCol(int col, char c);

		// Misc. helper methods
		void		drawBoardToScreen(char **board);
		char		**adjustBoardToScreen(Vector2D maxWinDem);
	};

	// To print the board info
	std::ostream      &operator<<(std::ostream &o, Board const &i);

#endif
