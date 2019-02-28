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
    Vector2D<float> v4(2.0f, 5.0f);

    std::cout << v1 + v2 << std::endl;
    std::cout << v1 / v2 << std::endl;
    std::cout << v1 * (uint_fast32_t)3 << std::endl;
    std::cout << (uint_fast32_t)3 * v1 << std::endl;
    std::cout << v3 / v4 << std::endl;
    // Initialize a new game called my game
    //Game myGame;

    // Run the game
    //myGame.run();

    // On exit return 0
    return 0;
}
