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

#include "Guessing.class.hpp"

template<typename T>
Guessing<T>::Guessing(std::vector<T> guessingList, T playerInput) : _guessingList(guessingList), _playerInput(playerInput) {
    return;
}

template<typename T>
Guessing<T>::Guessing(Guessing const &src) {
    *this = src;
    return;
}

template<typename T>
Guessing<T>::~Guessing(void) {
    return;
}

template<typename T>
Guessing<T>&        Guessing<T>::operator=(const Guessing& rhs) {
	if (this != &rhs) {
		this->_guessingList = rhs.getGuessingList();
		this->_playerInput = rhs.getPlayerInput();
	}
	return *this;
}

template<typename T>
std::vector<T>  Guessing<T>::getGuessingList(void) const {
    return this->_guessingList;
}

template<typename T>
T               Guessing<T>::getPlayerInput(void) const {
    return this->_playerInput;
}

/*
template<typename T>
int             Guessing<T>::binarySearch(int start, int end, const T& key)
{
    // Termination condition: start index greater than end index
    if(start > end) return -1;

    // Find the middle element of the vector and use that for splitting
    // the array into two pieces.
    const int middle = start + ((end - start) / 2);

    if(_guessingList[middle] == key) return middle;
    else if(_guessingList[middle] > key) return binary_search(start, middle - 1, key);
    else return binary_search(middle + 1, end, key);
}
*/
