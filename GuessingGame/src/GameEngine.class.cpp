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
#include <time.h>
#include <ncurses.h>
#include <typedefs.hpp>
#include "Vector2D.class.hpp"
#include "GameState.class.hpp"
#include "GameEngine.class.hpp"

// Initializing the static window to null
WINDOW						*GameEngine::_window = nullptr;

GameEngine::GameEngine(void) {
	GameEngine::_window = initscr();
	return;
}

GameEngine::~GameEngine(void) {
	GameEngine::_window = nullptr;
	return;
}

// Static Getters --
WINDOW*						GameEngine::getWindow(void) {
	return GameEngine::_window;
}

// Static check the win demensions
bool						GameEngine::isWindowToSmall(const Vector2D<uint_fast32_t> v) {
	if (v.x > MIN_WIN_SIZE && v.y > MIN_WIN_SIZE) return false;
	return true;
}

float						GameEngine::calculateFPS(void) {
	static int		frames = 0;
	static double	startTime = 0;
	static bool		first = TRUE;
	static float	fps = 0.0f;
	static time_t	systemTime = time (NULL);
	float			timePassed = time(NULL) - systemTime;

	if (first)
	{
	    frames = 0;
	    startTime = timePassed;
	    first = FALSE;
	    return 0.0;
	}
	frames++;
	if (timePassed - startTime > 0.25 && frames > 10)
	{
	    fps = (double) frames / (timePassed - startTime);
	    startTime = timePassed;
	    frames = 0;
	}
	return fps;
}

void						GameEngine::printMiddle(const Vector2D<uint_fast32_t> pos, const std::string msg) {
	std::vector<std::string> strs;

	strs = split(msg, '\n');
	for (unsigned int i = 0; i < strs.size(); i++)
		mvprintw(HALF_OF_VAL(pos.y) + i, HALF_OF_VAL(pos.x) - HALF_OF_VAL(strs[i].length()), strs[i].c_str());
}

void						GameEngine::printPos(const Vector2D<uint_fast32_t> pos, const std::string msg) {
	std::vector<std::string> strs;

	strs = split(msg, '\n');
	for (unsigned int i = 0; i < strs.size(); i++)
		mvprintw(pos.y + i, pos.x - HALF_OF_VAL(strs[i].length()), strs[i].c_str());
}

void						GameEngine::printBorder() {
	wborder(GameEngine::getWindow(), BORDER_SIDES, BORDER_SIDES, BORDER_TOP_BOTTOM, BORDER_TOP_BOTTOM, BORDER_CORNERS, BORDER_CORNERS, BORDER_CORNERS, BORDER_CORNERS);
}

// Run the window loop
void						GameEngine::start(void) {
	GameState *gameState = new GameState(Vector2D<uint_fast32_t>(5));

	_initWindow();
	_updateWinDem(*gameState);
	do {
		_updateWinDem(*gameState);
		_handleInput(*gameState);
		if (!gameState->runState()) break;
		wrefresh(GameEngine::_window);
	} while(true);
	delete gameState;
	_destroyWin();
	return;
}

// Update the win demension
void						GameEngine::_updateWinDem(GameState& gameState) {
	unsigned int x, y;

	getmaxyx(GameEngine::_window, y, x);
	gameState.setWinDem(Vector2D<uint_fast32_t>(x, y));
}

void					GameEngine::_handleInput(GameState& gameState) {
	gameState.handleInput(wgetch(GameEngine::_window));
}

void						GameEngine::_initWindow(void) {
	cbreak();
	noecho();
	clear();
	wrefresh(GameEngine::_window);
	keypad(GameEngine::_window, true);
	nodelay(GameEngine::_window, true);
	curs_set(0);
	/* Because I do not use colors yet --
	if (!has_colors()) {
		std::cout << "Error: Terminal does not support color" << std::endl;
		return;
	}
	start_color();
	*/
}

// Destroy the window and clear any artifacts
void						GameEngine::_destroyWin(void) {
	wborder(GameEngine::_window, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
	wrefresh(GameEngine::_window);
	delwin(GameEngine::_window);
	clear();
	endwin();
	return;
}

// To print out all of the games attributes
std::ostream				&operator<<(std::ostream &o, GameEngine const &i) {
	return o << "Game Thread Info:" << std::endl <<
	"Window addr: " << i.getWindow() << std::endl;
}

std::vector<std::string>	split(const std::string& s, char const delimiter)
{
   std::vector<std::string> tokens;
   std::string token;
   std::istringstream tokenStream(s);

   while (std::getline(tokenStream, token, delimiter)) tokens.push_back(token);
   return tokens;
}
