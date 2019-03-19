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

#include <vector>
#include <sstream>
#include <ncurses.h>
#include <typedefs.hpp>
#include "Vector2D.class.hpp"
#include "Timer.class.hpp"
#include "GameStateHandler.class.hpp"
#include "GameEngine.class.hpp"

// Initializing the static window to null
GameStateHandler					*GameEngine::_gameStateHandler = nullptr;

// Getters --
GameStateHandler*					GameEngine::getGameStateHandler(void) {
	return GameEngine::_gameStateHandler;
}

// Clear the screen without including ncurses
void                 		GameEngine::clearScreen(void) {
	clear();
}

// Static check the win dimensions
bool						GameEngine::isWindowToSmall(void) {
	if (COLS > MIN_WIN_SIZE && LINES > MIN_WIN_SIZE)
		return false;
	return true;
}

// Static get the fps based on a 0.25 sec interval
float						GameEngine::calculateFPS(void) {
	static int		frames = 0;
	static Timer	systemTime;
	static float	fps = 0.0f;
	double 			elapsed = systemTime.elapsed();

	frames++;
	if (elapsed > 0.25 && frames > 10) {
	    fps = (double) frames / elapsed;
		systemTime.reset();
	    frames = 0;
	}
	return fps;
}

// Print a message to the center of the screen
void						GameEngine::printMiddle(const std::string msg) {
	std::vector<std::string> strs;

	strs = split(msg, '\n');
	for (unsigned int i = 0; i < strs.size(); i++)
		mvprintw(HALF_OF_VAL(LINES) + i, HALF_OF_VAL(COLS) - HALF_OF_VAL(strs[i].length()), strs[i].c_str());
}

// Print a message at the specified point
void						GameEngine::printPos(const Vector2D<uint_fast32_t> pos, const std::string msg) {
	std::vector<std::string> strs;

	strs = split(msg, '\n');
	for (unsigned int i = 0; i < strs.size(); i++)
		mvprintw(pos.y + i, pos.x - HALF_OF_VAL(strs[i].length()), strs[i].c_str());
}

// Print the boarder around the screen
void						GameEngine::printBorder(void) {
	wborder(stdscr, BORDER_SIDES, BORDER_SIDES, BORDER_TOP_BOTTOM, BORDER_TOP_BOTTOM, BORDER_CORNERS, BORDER_CORNERS, BORDER_CORNERS, BORDER_CORNERS);
}

// Add an attribute for the selected menu item only
void                 		GameEngine::useMenuTitleAttr(bool bUse) {
	if (bUse) attron(A_BOLD | A_UNDERLINE);
	else attroff(A_BOLD | A_UNDERLINE);
}

// Add an attribute for the selected menu item only
void                 		GameEngine::useMenuItemAttr(bool bUse) {
	if (bUse) attron(A_STANDOUT | A_BOLD | A_BLINK);
	else attroff(A_STANDOUT | A_BOLD | A_BLINK);
}

// Run the window loop
void						GameEngine::start(void) {
	GameEngine::_gameStateHandler = new GameStateHandler(Vector2D<uint_fast32_t>(MIN_WIN_SIZE + 5));

	GameEngine::_initWindow();
	do {
		GameEngine::_resizeHandler();
		GameEngine::_handleInput();
		if (!GameEngine::_gameStateHandler->runState())
			break;
		refresh();
	} while(true);
	GameEngine::_destroyWin();
	delete GameEngine::_gameStateHandler;
	GameEngine::_gameStateHandler = nullptr;
}

// Handle window resize
void                		GameEngine::_resizeHandler(void) {
	GameEngine::_gameStateHandler->setWinDem(Vector2D<uint_fast32_t>(COLS, LINES));
}

// Handle the input for the game state
void						GameEngine::_handleInput(void) {
	int input;
	if ((input = getch()) != ERR)
		GameEngine::_gameStateHandler->handleInput(input);
}

// Initialize the window with ncurses
void						GameEngine::_initWindow(void) {
	initscr();
	cbreak();
	noecho();
	keypad(stdscr, true);
	nodelay(stdscr, true);
	curs_set(0);
	/* Because I do not use colors yet --
	if (!has_colors()) {
		std::cout << "Error: Terminal does not support color" << std::endl;
		return;
	}
	start_color();
	*/
	clear();
}

// Destroy the window and clear any artifacts
void						GameEngine::_destroyWin(void) {
	wborder(stdscr, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
	refresh();
	clear();
	endwin();
	return;
}

// To print out all of the games attributes
std::ostream				&operator<<(std::ostream &o, GameEngine const &i) {
	return o << "Game Thread Info:" << std::endl <<
	"Game State: " << i.getGameStateHandler() << std::endl;
}

// Global function to help me split strings
std::vector<std::string>	split(const std::string& s, char const delimiter)
{
	std::vector<std::string> tokens;
   	std::string token;
   	std::istringstream tokenStream(s);

   	while (std::getline(tokenStream, token, delimiter))
   		tokens.push_back(token);
   	return tokens;
}
