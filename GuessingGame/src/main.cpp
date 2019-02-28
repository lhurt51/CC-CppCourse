/******************************************************************************
* Programmer Name:
* Liam Hurt
*
* Date:
* 2/6/2019
*
* Assignment Requirement:
* Develop and test a connect - 4 like game except:
*
* Only need to connect 3
* There will be 3 players
* Only need to connect vertical and horizontal
* Use a board of 5 by 6 with header for the column number
* Use ASCII graphics
*
******************************************************************************/

//#include "Game.class.hpp"
#include "Vector2D.class.hpp"

int main() {
    Vector2D<uint_fast32_t> v1(4, 5);
    Vector2D<uint_fast32_t> v2(2, 2);
    Vector2D<float> v3(7.0f, 11.0f);

    std::cout << v1 << std::endl;
    v1 /= v2;
    std::cout << v1 << std::endl;
    v1 *= 10;
    std::cout << v1 << std::endl;
    v1 /= 2;
    std::cout << v1 << std::endl;
    v3 /= 2.0f;
    std::cout << v3 << std::endl;
    // Initialize a new game called my game
    //Game myGame;

    // Run the game
    //myGame.run();

    // On exit return 0
    return 0;
}
