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

#include <time.h>
#include <sstream>
#include <typedefs.hpp>
#include "GameEngine.class.hpp"
#include "GameState.class.hpp"

// Initializing the static window to null
WINDOW					*GameEngine::_window = nullptr;

GameEngine::GameEngine(void) {
	GameEngine::_window = initscr();
	return;
}

GameEngine::~GameEngine(void) {
	GameEngine::_window = nullptr;
	return;
}

// Static Getters --
WINDOW*					GameEngine::getWindow(void) {
	return GameEngine::_window;
}

// Static check the win demensions
bool            		GameEngine::isWindowToSmall(const Vector2D<uint_fast32_t> v) {
	if (v.x > MIN_WIN_SIZE && v.y > MIN_WIN_SIZE) return false;
	return true;
}

float                GameEngine::calculateDT(void) {
	static time_t	systemTime = time (NULL);
	float			timePassed = time(NULL) - systemTime;
	return timePassed;
}

float                	GameEngine::calculateFPS(void) {
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

void                 GameEngine::printMiddle(const Vector2D<uint_fast32_t> pos, const std::string msg, const bool clear) {
	std::vector<std::string> strs;

	strs = split(msg, '\n');
	for (unsigned int i = 0; i < strs.size(); i++) {
		unsigned int halfOfString = HALF_OF_VAL(strs[i].length());

		if (!clear) mvprintw(HALF_OF_VAL(pos.y + i), HALF_OF_VAL(pos.x) - halfOfString, strs[i].c_str());
		else
		{
			for (unsigned int j = -halfOfString; j < halfOfString; j++ )
				mvaddch(HALF_OF_VAL(pos.y + i), HALF_OF_VAL(pos.x) + j, ' ');
		}
	}
}

// Run the window loop
void					GameEngine::start(void) {
	GameState *gameState;

	gameState = new GameState(Vector2D<uint_fast32_t>(5));
	clear();
	_updateWinDem(*gameState);
	_initWindow();
	do {
		/*
		if (gameState->getCurState() == EXITING) break;
		Game::updateWinDem(*gameState);
		gameState->runMainLoop();
		*/
		gameState->runState(0.0f);
		wrefresh(GameEngine::_window);
	} while(true);
	delete gameState;
	_destroyWin();
	return;
}

// Static update the win demension
void        			GameEngine::_updateWinDem(GameState& gameState) {
	unsigned int x, y;

	getmaxyx(GameEngine::_window, y, x);
	gameState.setWinDem(Vector2D<uint_fast32_t>(x, y));
}

void                 	GameEngine::_initWindow(void) {
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
void        			GameEngine::_destroyWin(void) {
	wborder(GameEngine::_window, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
	wrefresh(GameEngine::_window);
	delwin(GameEngine::_window);
	endwin();
	return;
}

// To print out all of the games attributes
std::ostream			&operator<<(std::ostream &o, GameEngine const &i) {
	return o << "Game Thread Info:" << std::endl <<
	"Window addr: " << i.getWindow() << std::endl;
}

std::vector<std::string> split(const std::string& s, char delimiter)
{
   std::vector<std::string> tokens;
   std::string token;
   std::istringstream tokenStream(s);

   while (std::getline(tokenStream, token, delimiter))
   {
      tokens.push_back(token);
   }
   return tokens;
}
