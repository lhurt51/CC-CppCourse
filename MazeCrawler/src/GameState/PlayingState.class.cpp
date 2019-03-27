/*******************************************************************************\
* Programmer Name:																*
* Liam Hurt																		*
*																				*
* Date:																			*
* 3/16/2019																		*
*																				*
* Assignment Requirement:														*
* 7.33 (Maze Traversal) The grid of hashes (#) and dots (.) in Fig. 7.29 is a	*
* two-dimensional builtin array representation of a maze. In the				*
* two-dimensional built-in array, the hashes represent the walls of the maze	*
* and the dots represent squares in the possible paths through the maze. Moves	*
* can be made only to a location in the built-in array that contains a dot.		*
* There is a simple algorithm for walking through a maze that guarantees to		*
* find the exit (assuming that there is an exit). If there is not an exit,		*
* you’ll arrive at the starting location again. Place your right hand on		*
* the wall to your right and begin walking forward. Never remove your hand		*
* from the wall. If the maze turns to the right, you follow the wall to the		*
* right. As long as you do not remove your hand from the wall, eventually		*
* you’ll arrive at the exit of the maze. There may be a shorter path than the	*
* one you’ve taken, but you are guaranteed to get out of the maze if you		*
* follow the algorithm.															*
*																				*
*  # # # # # # # # # # # #														*
*  # . . . # . . . . . . #														*
*  . . # . # . # # # # . #														*
*  # # # . # . . . . # . #														*
*  # . . . . # # # . # . .														*
*  # # # # . # . # . # . #														*
*  # . . # . # . # . # . #														*
*  # # . # . # . # . # . #														*
*  # . . . . . . . . # . #														*
*  # # # # # # . # # # . #														*
*  # . . . . . . # . . . #														*
*  # # # # # # # # # # # #														*
*																				*
* Write recursive function mazeTraverse to walk through the maze. The function	*
* should receive arguments that include a 12-by-12 built-in array of chars		*
* representing the maze and the starting location of the maze. As mazeTraverse	*
* attempts to locate the exit from the maze, it should place the character X	*
* in each square in the path. The function should display the maze after each	*
* move, so the user can watch as the maze is solved.							*
*																				*
\*******************************************************************************/

#include <macros/main_game_macros.hpp>
#include "Vector2D.class.hpp"
#include "GameObjects/Actors/Maze/Maze.class.hpp"
#include "PlayingState.class.hpp"
#include "Handlers/MenuHandler.class.hpp"
#include "Handlers/GameStateHandler.class.hpp"

// Initializer for window dimensions Constructor
PlayingState::PlayingState(void) : GameState() {
	MenuHandler::setMenu(1);
	_maze = new Maze(Vector2D<uint_fast32_t>(HALF_OF_VAL(GameStateHandler::getWinDim().x), 9));
	return;
}

// Copy constructor
PlayingState::PlayingState(PlayingState const &src) : GameState(src) {
	*this = src;
	return;
}

// De-constructor
PlayingState::~PlayingState(void) {
	MenuHandler::deleteMenu();
	delete _maze;
	return;
}

// Equal sign overload for the copy constructor
PlayingState					&PlayingState::operator=(PlayingState const &rhs) {
	if (this != &rhs) {}
	return *this;
}

void							PlayingState::handleResize(void) {
	_maze->setPos(Vector2D<uint_fast32_t>(HALF_OF_VAL(GameStateHandler::getWinDim().x), 9));
	MenuHandler::handleResize();
}

void							PlayingState::handleInput(int input) {
	MenuHandler::handleInput(input);
}

void							PlayingState::handleTick(void) {
	GameState::handleTick();
}

// Out stream overload for testing
std::ostream					&operator<<(std::ostream &o, PlayingState const &i) {
	return o << "Game State Info:" << &i << std::endl;
}
