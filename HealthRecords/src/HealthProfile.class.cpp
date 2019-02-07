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
#include <ctime>
#include <math.h>

// Constructor needs to validate inputs but for now this works
HealthProfile::HealthProfile(std::string firstName, std::string lastName, std::string gender, int dOB, int mOB, int yOB, int weight, int height) {
	this->_firstName = firstName;
	this->_lastName = lastName;
	this->_gender = gender;
	this->_dOB = dOB;
	this->_mOB = mOB;
	this->_yOB = yOB;
	this->_weight = weight;
	this->_height = height;
	return;
}

// Copy constructor to copy the HealthProfile
HealthProfile::HealthProfile(HealthProfile const &src) {
	*this = src;
	return;
}

// Overload for the equal sign so we can say *this = src in copy constructor
HealthProfile		&HealthProfile::operator=(HealthProfile const &rhs) {
	if (this != &rhs) {
		this->_firstName = rhs.getFirstName();
		this->_lastName = rhs.getLastName();
		this->_gender = rhs.getGender();
		this->_dOB = rhs.getDOB();
		this->_mOB = rhs.getMOB();
		this->_yOB = rhs.getYOB();
		this->_weight = rhs.getWeight();
		this->_height = rhs.getHeight();
	}
	return *this;
}

// All my getters and setters start here
std::string			HealthProfile::getFirstName(void) const {
	return this->_firstName;
}

std::string			HealthProfile::getLastName(void) const {
	return this->_lastName;
}

std::string			HealthProfile::getGender(void) const {
	return this->_gender;
}

int               	HealthProfile::getDOB(void) const {
	return this->_dOB;
}

int               	HealthProfile::getMOB(void) const {
	return this->_mOB;
}

int               	HealthProfile::getYOB(void) const {
	return this->_yOB;
}

int									HealthProfile::getWeight(void) const {
	return this->_weight;
}

int									HealthProfile::getHeight(void) const {
	return this->_height;
}

// I realize for my setters I could have been more maticulous about error catching
// but I figured since we havent learned much about error handling I should just leave it
bool         				HealthProfile::setFirstName(std::string firstName) {
	if (firstName.empty() || firstName == "")
		return false;
	this->_firstName = firstName;
	return true;
}

bool         		HealthProfile::setLastName(std::string lastName) {
	if (lastName.empty() || lastName == "")
		return false;
	this->_lastName = lastName;
	return true;
}

bool          		HealthProfile::setGender(std::string gender) {
	if (gender.empty() || gender == "" || (gender != "M" && gender != "F" && gender != "O"))
		return false;
	this->_gender = gender;
	return true;
}

bool          		HealthProfile::setDOB(int dOB) {
	if (dOB < 1 || dOB > 31)
		return false;
	this->_dOB = dOB;
	return true;
}

bool          		HealthProfile::setMOB(int mOB) {
	if (mOB < 1 || mOB > 12)
		return false;
	this->_mOB = mOB;
	return true;
}

bool          		HealthProfile::setYOB(int yOB) {
	if (yOB < 1900 || yOB > 2018)
		return false;
	this->_yOB = yOB;
	return true;
}

bool          		HealthProfile::setWeight(int weight) {
	if (weight < 1 || weight > 2000)
		return false;
	this->_weight = weight;
	return true;
}

bool          		HealthProfile::setHeight(int height) {
	if (height < 1 || height > 200)
		return false;
	this->_height = height;
	return true;
}
// End of getters and setters

// Method for calculating age
int								HealthProfile::calculateAge(void) const {
	time_t now = time(0);
	tm *ltm = localtime(&now);
	int curYear = 1900 + ltm->tm_year;
	int curMon = 1 + ltm->tm_mon;
	int curDay = ltm->tm_mday;
	int age = curYear - this->_yOB - 1;

	if (curMon >= this->_mOB) {
		if (curMon == this->_mOB) {
			if (curDay >= this->_dOB) age++;
		} else age++;
	}
	return age;
}

// Method for calculating Max Heart Rate
int           			HealthProfile::calculateMHR(void) const {
	return 207 - (0.67 * this->calculateAge());
}

// Method to calculate and print the Target Heart Rate because it is a range
std::string         HealthProfile::calculateTHR(void) const {
	int mHR = this->calculateMHR();
	int lowTHR = (float)mHR * 0.5;
	int highTHR = (float)mHR * 0.85;
	return std::to_string(lowTHR) + " - " + std::to_string(highTHR);
}

// Calculating body mass index
float           		HealthProfile::calculateBMI(void) const {
	return roundf(((float)(this->_weight * 703) / (float)(this->_height * this->_height)) * 100) / 100;
}

// Prints out the BMI values table
std::string         HealthProfile::printBMIVal(void) const {
	return "\nBMI VALUES\nUnderweight: less than 18.5\nNormal:      between 18.5 and 24.9\nOverweight:  between 25 and 29.9\nObese:       30 or greater";
}

// Overloads the << operator so I can use this to print the entire profile
std::ostream				&operator<<(std::ostream &o, HealthProfile const &i) {
	o << std::endl;
	o << i.getFirstName() << " " << i.getLastName() << "'s health profile." << std::endl;
	o << "Date of Birth: " << i.getMOB() << "/" << i.getDOB() << "/" << i.getYOB() << std::endl;
	o << "Age: " << i.calculateAge() << std::endl;
	o << "Gender: " << i.getGender() << std::endl;
	o << "Weight: " << i.getWeight() << "lbs" << std::endl;
	o << "Height: " << i.getHeight() << "in" << std::endl;
	o << "MHR: " << i.calculateMHR() << std::endl;
	o << "THR: " << i.calculateTHR() << std::endl;
	o << "BMI: " << i.calculateBMI() << std::endl;
	o << i.printBMIVal() << std::endl;
	return o;
}
