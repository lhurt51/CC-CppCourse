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

#include "Vector2D.class.hpp"
#include "GameObject.class.hpp"
#include "GameEngine.class.hpp"

// Default constructor
GameObject::GameObject(Vector2D<uint_fast32_t> pos, std::string const sprite) : _bCanDraw(true), _pos(pos), _sprite(sprite) {
	return;
}

// Copy constructor
GameObject::GameObject(GameObject const &src) : _sprite(src.getSprite()) {
	*this = src;
	return;
}

// Default deconstructor
GameObject::~GameObject(void) {
	return;
}

// Equal sign overload
GameObject					&GameObject::operator=(GameObject const &rhs) {
	if (this != &rhs) {
		this->_bCanDraw = rhs.getCanDraw();
		this->_pos = rhs.getPos();
		(std::string&)this->_sprite = rhs.getSprite();
	}
	return *this;
}

// Getters --
bool					GameObject::getCanDraw(void) const {
	return this->_bCanDraw;
}

Vector2D<uint_fast32_t>	GameObject::getPos(void) const {
	return this->_pos;
}

std::string	const		GameObject::getSprite(void) const {
	return this->_sprite;
}

// Setters --
void					GameObject::setCanDraw(bool bCanDraw) {
	if (this->_bCanDraw != bCanDraw)
		this->_bCanDraw = bCanDraw;
}

void 					GameObject::setPos(Vector2D<uint_fast32_t> pos) {
	if (this->_pos != pos)
		this->_pos = GameEngine::checkGameObjectPos(pos, _sprite);
}

void 					GameObject::draw(void) {
	if(_bCanDraw) GameEngine::printPos(_pos, _sprite);
}

// Output pverload for testing
std::ostream			&operator<<(std::ostream &o, GameObject const &i) {
	return o << "GameObject Info:" << std::endl <<
	"can draw: " << i.getCanDraw() << std::endl <<
	"pos: " << i.getPos() << std::endl <<
	"sprite: " << i.getSprite() << std::endl;
}
