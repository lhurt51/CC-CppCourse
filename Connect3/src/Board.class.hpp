#ifndef BOARD_CLASS_HPP
	#define BOARD_CLASS_HPP

	#include "Actor.class.hpp"

	class Board : public Actor {

		// A 2D char array acting as a board
		char		**_board;
		// A vector for the player to spawn at
		Vector2D	_playerSpawn;

	public:
		// Constructors --
		Board(void);
		Board(Vector2D pos);
		Board(Board const &src);
		~Board(void);

		// Overload operators --
		Board		&operator=(Board const &rhs);

		// Getters --
		char		**getBoard(void) const;
		Vector2D	getPlayerSpawn(void) const;

		// Setters --
		void		initBoard(void);
		bool		addPieceToPoint(int row, int col, char c);

		// Destructor --
		void		deleteBoard(void);

		// Misc. helper methods --
		bool		isColFull(int col) const;
		bool		isColEmpty(int col) const;
		Vector2D	worldToBoard(Vector2D world);

		// Actor method implementation --
		void		tick(void);

	protected:

		// Overload Actor Methods --
		void 		_checkPos(void);
		void		_draw(void) const;
		void 		_clear(void) const;

	private:

		// Private print functions --
		void		_drawBoardToScreen(bool clear) const;
		void		_drawBoardColToScreen(bool clear, int col) const;
		void		_printChar(bool clear, char c, int x, int y) const;
	};

	// To print the board info
	std::ostream      &operator<<(std::ostream &o, Board const &i);

#endif
