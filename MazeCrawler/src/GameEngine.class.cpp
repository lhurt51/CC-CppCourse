/******************************************************************************
* Programmer Name:
* Liam Hurt
*
* Date:
* 2/6/2019
*
* Assignment Requirement:
* - Ask the user to guess a whole number between 1 and 1000 or character 'A'
*   to 'Z'
* - Your program will try to find the number
* - Keep track of the number of guesses by the computer
* - Use Recursive one of two search techniques: linear search or binary search
*   or randomize guess of a number.
* - Use a template class so the program could be used for integer or character,
*   your test function within your class should run with integer first then a
*   character
* - Use a randomized random number or letter generator for the item to guess
* - Allow the computer to have only 15 guesses
* - Your game class will have two functions or methods: playTheGame and static
*   Test
* - Your game shall have two modes: automatic where the computer tries to guess
*   you number without any input from you (except for the guess number) and
*   manual mode where each guess of the computer requires your input of Higher,
*   Lower, Right
*
******************************************************************************/

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

// Static check the win demensions
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
	GameEngine::_gameStateHandler->handleInput(getch());
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
