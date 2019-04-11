/*******************************************************************************\
* Programmer Name:																*
* Liam Hurt																		*
*																				*
* Date:																			*
* 4/10/2019																		*
*																				*
* Assignment Requirement:														*
* - Make a program that rolls a 6 sided die and prints to the screen            *
*																				*
\*******************************************************************************/

#include <iostream>
#include <vector>
#include <string>
#include <thread>

// Provided func for sleeping the thread in milliseconds
void sleepInMilliseconds(unsigned int milliseconds) {
    std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
}

// Provided class header
class Dice {

    // Constant sprite inline declaration - Only works for C++11
    const std::vector<std::vector<std::string>> sprite = {
        { "+-----------+","|           |","|     O     |","|           |","+-----------+" }, // 1
        { "+-----------+","| O         |","|           |","|         O |","+-----------+" }, // 2
        { "+-----------+","| O         |","|     O     |","|         O |","+-----------+" }, // 3
        { "+-----------+","| O       O |","|           |","| O       O |","+-----------+" }, // 4
        { "+-----------+","| O       O |","|     O     |","| O       O |","+-----------+" }, // 5
        { "+-----------+","| O       O |","| O       O |","| O       O |","+-----------+" }  // 6
    };

    // Constant sprites number declaration - Only works in C++11
    const unsigned int dieFACES = sprite.size();

public:

    // used for each loop through the game to change sprite
    unsigned int rollIT(void);

private:

    // Drawing sprites to the screen
    void draw(unsigned int number);

};

unsigned int Dice::rollIT(void)
{
    // Gets rand num between 0 and 6
    int rollI = rand() % 6;

    // Draw the selected sprite
    draw(rollI);
    // Sleep for half a second
    sleepInMilliseconds(500);
    return rollI;
}

void Dice::draw(unsigned int number)
{
    // Makes sure number is a valid input
    if (number > dieFACES) return;
    // Clear the screen
    system("clear");
    // Used for formating
    for (unsigned int i = 0; i < 5; i++)
        std::cout << std::endl;

    // Set variable of the selected sprite
    std::vector<std::string> strs = sprite[number];
    // For each string in the sprite print with end line
    for (std::string str : strs)
        std::cout << "\t\t" << str << std::endl;
}


int main(void) {
    // Create a dice
    Dice die;

    // Run game loop
    do {
        // Rool dice
        die.rollIT();
    } while (true);

    // Return succes on control^c quit
    return 0;
}
