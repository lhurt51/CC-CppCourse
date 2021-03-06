/*******************************************************************************\
* Programmer Name:																*
* Liam Hurt																		*
*																				*
* Date:																			*
* 3/28/2019																		*
*																				*
* Assignment Requirement:														*
* This program will play a slot machine game. The slot machine shall have 3     *
* slots (or a single number between 0 to 9 for each slot) of the following      *
* ASCII number vector to use (see below). The user shall have the ability to    *
* make a bet and then the game will automatically spin the digits. Use a delay  *
* to simulate the numbers changing before the final numbers are revealed (if    *
* you use C++ 11 see the function below). The following conditions will be      *
* programmed:                                                                   *
*                                                                               *
* 3 matching numbers win 10 times the bet                                       *
*                                                                               *
* 2 matching numbers win 5 times the bet                                        *
*                                                                               *
* no matching number losses the bet				                     			*
*																				*
\*******************************************************************************/

#include <vector>
#include <sstream>
#include <math.h>
#include <ncurses.h>
#include <macros/main_game_macros.hpp>
#include "Vector2D.class.hpp"
#include "Timers/Timer.class.hpp"
#include "Handlers/GameStateHandler.class.hpp"
#include "GameEngine.class.hpp"


// Clear the screen without including ncurses
void                 		GameEngine::clearScreen(void) {
	clear();
}

// Refresh the screen without including ncurses
void                 		GameEngine::refreshScreen(void) {
	refresh();
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
	return round(fps);
}

Vector2D<uint_fast32_t>  	GameEngine::checkGameObjectPos(Vector2D<uint_fast32_t> pos, const std::string msg) {
	std::vector<std::string>	strs;
	unsigned					halfLength;
	unsigned					halfHeight;

	strs = split(msg, '\n');
	halfLength = HALF_OF_VAL(maxStringLength(strs)) + 2;
	halfHeight = HALF_OF_VAL(strs.size()) + 2;
	if ((int)(pos.x) - (int)(halfLength) < 0)
		pos.x = halfLength;
	else if ((int)(pos.x + halfLength) >= COLS)
		pos.x = COLS - halfLength;
	if ((int)(pos.y) - (int)(halfHeight) < 0)
		pos.y = halfHeight;
	else if ((int)(pos.y + halfHeight) >= LINES)
		pos.y = LINES - halfHeight;
	return pos;
}

Vector2D<uint_fast32_t>  	GameEngine::gameObjectSpriteDim(const std::string msg) {
	std::vector<std::string> strs;

	strs = split(msg, '\n');
	return Vector2D<uint_fast32_t>(maxStringLength(strs), strs.size());
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
		mvprintw(pos.y - HALF_OF_VAL(strs.size()) + i, pos.x - HALF_OF_VAL(strs[i].length()), strs[i].c_str());
}

// Print the boarder around the screen
void						GameEngine::printBorder(void) {
	border(BORDER_SIDES, BORDER_SIDES, BORDER_TOP_BOTTOM, BORDER_TOP_BOTTOM, BORDER_CORNERS, BORDER_CORNERS, BORDER_CORNERS, BORDER_CORNERS);
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

// Add an attribute for the selected menu item only
void                 		GameEngine::usePathFollowerAttr(bool bUse) {
	if (bUse) attron(A_STANDOUT | A_BOLD);
	else attroff(A_STANDOUT | A_BOLD);
}

// Run the window loop
void						GameEngine::start(void) {
	GameEngine::_initWindow();
	do {
		GameEngine::_resizeHandler();
		GameEngine::_handleInput();
		if (!GameStateHandler::runState())
			break;
	} while(true);
	GameEngine::_destroyWin();
}

// Handle window resize
void                		GameEngine::_resizeHandler(void) {
	GameStateHandler::setWinDim(Vector2D<uint_fast32_t>(COLS, LINES));
}

// Handle the input for the game state
void						GameEngine::_handleInput(void) {
	int input;
	if ((input = getch()) != ERR)
		GameStateHandler::handleInput(input);
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
	border(' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
	refresh();
	clear();
	endwin();
	return;
}

// To print out all of the games attributes
std::ostream				&operator<<(std::ostream &o, GameEngine const &i) {
	return o << "Game Thread Info:" << &i << std::endl;
}

unsigned					maxStringLength(std::vector<std::string> strs) {
	unsigned maxLength = 0;
	for (std::string str : strs) {
		if (maxLength < str.length()) maxLength = str.length();
	}
	return maxLength;
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
