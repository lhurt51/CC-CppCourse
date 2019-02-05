/******************************************************************************
* Programmer Name:
* Liam Hurt
*
* Date:
* 1/25/19
*
* Assignment Requirement:
* 2.23 (Largest and Smallest Integers) Write a program that reads in five
* integers and determines and prints the largest and the smallest integers in
* the group. Use only the programming techniques you learned in this chapter.
*
******************************************************************************/

#include <iostream>

// Using namespace for cleaner code
using namespace std;

// Running the program with the main
int main() {
	// Declaring an integers for the user to enter along with a min max value
	int num1, num2, num3, num4, num5, smallest, largest;

	// Declaring the smallest var as int max and vic versa.
	smallest = INT_MAX;
	largest = INT_MIN;

	// Asking user for input
	cout << "Enter five integers: " << endl;
	// Accepting 5 int inputs
	cin >> num1 >> num2 >> num3 >> num4 >> num5;

	/* Checking each number agains smallest and largest		*
	*  WARNING!!!!! -- this does not handle int max or min	*
	*  Answer will always be even if min or max is exceded	*/
	if (num1 < smallest) smallest = num1;
	if (num2 < smallest) smallest = num2;
	if (num3 < smallest) smallest = num3;
	if (num4 < smallest) smallest = num4;
	if (num5 < smallest) smallest = num5;
	if (num1 > largest) largest = num1;
	if (num2 > largest) largest = num2;
	if (num3 > largest) largest = num3;
	if (num4 > largest) largest = num4;
	if (num5 > largest) largest = num5;

	// Printing the final answer for the smallest adn largest numbers
	cout << "Smallest value: " << smallest << endl << "Largest value: " << largest << endl;
	return 0;
}
