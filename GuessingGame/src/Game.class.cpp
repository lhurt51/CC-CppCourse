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

#include <typedefs.hpp>
#include <time.h>
#include "Game.class.hpp"
#include "GameState.class.hpp"

// Initializing the static window to null
WINDOW					*Game::_window = nullptr;

// Getters --
WINDOW*					Game::getWindow(void) {
	return Game::_window;
}

void                 	Game::initWindow(void) {
	Game::_window = initscr();
	cbreak();
	noecho();
	clear();
	wrefresh(Game::_window);
	keypad(Game::_window, true);
	nodelay(Game::_window, true);
	curs_set(0);
	/* Because I do not use colors yet --
	if (!has_colors()) {
		std::cout << "Error: Terminal does not support color" << std::endl;
		return;
	}
	start_color();
	*/
	Game::calculateFPS();
}

// Update the win demension
void        			Game::updateWinDem(GameState& gameState) {
	unsigned int x, y;

	getmaxyx(Game::_window, y, x);
	gameState.setWinDem(Vector2D<uint_fast32_t>(x, y));
}

// Run the window loop
void					Game::run(void) {
	GameState *gameState;

	gameState = new GameState(Vector2D<uint_fast32_t>(5));
	clear();
	Game::updateWinDem(*gameState);
	do {
		if (gameState->getCurState() == EXITING) break;
		Game::updateWinDem(*gameState);
		gameState->runMainLoop();
		wrefresh(Game::_window);
	} while(true);
	delete gameState;
	return;
}

// Check the win demensions
bool            		Game::isWindowToSmall(void) {
	unsigned int x, y;

	getmaxyx(Game::_window, y, x);
	if (x > MIN_WIN_SIZE && y > MIN_WIN_SIZE) return false;
	return true;
}

float                	Game::calculateFPS(void) {
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

// Destroy the window and clear any artifacts
void        			Game::destroyWin(void) {
	wborder(Game::_window, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
	wrefresh(Game::_window);
	delwin(Game::_window);
	endwin();
	Game::_window = NULL;
	return;
}

// To print out all of the games attributes
std::ostream			&operator<<(std::ostream &o, Game const &i) {
	return o << "Game Thread Info:" << std::endl <<
	"Window addr: " << i.getWindow() << std::endl;
}
