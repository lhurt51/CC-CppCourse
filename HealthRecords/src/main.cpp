/******************************************************************************
* Programmer Name:
* Liam Hurt
*
* Date:
* 1/30/2019
*
* Assignment Requirement:
* 3.17 (Computerization of Health Records) A health care issue that has been in
* the news lately is the computerization of health records. This possibility is
* being approached cautiously because of sensitive privacy and security
* concerns, among others. [We address such concerns in later exercises.]
*
******************************************************************************/

#include "HealthProfile.class.hpp"

int main() {
    // Setting a default new health profile so I can use my setter functions
    HealthProfile newProf = HealthProfile("default", "default", "O", 1, 1, 1999, 130, 64);
    // Creating variables for my standard input
    std::string firstName, lastName, gender;
    int         dOB, mOB, yOB, weight, height;

    // Telling the user what to input... I know this is a very confusing UI atm.
    std::cout << "Please enter your first name, last name, gender, day of birth, month of birth, year of birth, weight in lbs, and hieght in inches" << std::endl;
    std::cout << "Enter in the order that it appears! For gender enter M for Male, F for Female, O for Other." << std::endl;
    // There is one problem with cin and that is when you enter a string for an int... Could fix with readline()
    std::cin >> firstName >> lastName >> gender >> dOB >> mOB >> yOB >> weight >> height;
    // Starting my checks with the class to check if the inputs are valid or not
    // THe while loop ensures that the user inputs the correct value
    while(!newProf.setFirstName(firstName)) {
        std::cout << "Enter a valid first name!" << std::endl;
        std::cin >> firstName;
    }
    while(!newProf.setLastName(lastName)) {
        std::cout << "Enter a valid last name!" << std::endl;
        std::cin >> lastName;
    }
    while(!newProf.setGender(gender)) {
        std::cout << "Enter a valid gender! Only enter M, F, O" << std::endl;
        std::cin >> gender;
    }
    while(!newProf.setDOB(dOB)) {
        std::cout << "Enter a valid day of birth! (1 - 31)" << std::endl;
        std::cin >> dOB;
    }
    while(!newProf.setMOB(mOB)) {
        std::cout << "Enter a valid month of birth! (1 - 12)" << std::endl;
        std::cin >> mOB;
    }
    while(!newProf.setYOB(yOB)) {
        std::cout << "Enter a valid year of birth! (1900 - 2018)" << std::endl;
        std::cin >> yOB;
    }
    while(!newProf.setWeight(weight)) {
        std::cout << "Enter a valid weight! (in lbs)" << std::endl;
        std::cin >> weight;
    }
    while(!newProf.setHeight(height)) {
        std::cout << "Enter a valid height! (in inches)" << std::endl;
        std::cin >> height;
    }

    // Printing out the entire profile
    std::cout << newProf << std::endl;
    return 0;
}
