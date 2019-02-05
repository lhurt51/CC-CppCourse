/******************************************************************************
* Programmer Name:
* Liam Hurt
*
* Date:
* 1/25/19
*
* Assignment Requirement:
* 2.24 (Odd or Even) Write a program that reads an integer and determines and
* prints whether it’s odd or even. [Hint: Use the modulus operator. An even
* number is a multiple of two. Any multiple of two leaves a remainder of zero
* when divided by 2.]
*
******************************************************************************/

#include <iostream>

// Using namespace for cleaner code
using namespace std;

// Running the program with the main
int main() {
	// Declaring an integer for the user to enter
	int input;

	// Printing to the user
	cout << "Enter an integer: ";
	// Accepting input from the user
	cin >> input;

	/* Checking for odd numbers by using modulos			*
	*  WARNING!!!!! -- this does not handle int max or min	*
	*  Answer will always be even if min or max is exceded	*/
	if(input % 2 == 1) cout << "The value is odd" << endl;
	else cout << "The value is even" << endl;

	return 0;
}
