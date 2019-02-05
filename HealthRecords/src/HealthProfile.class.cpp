#include "HealthProfile.class.hpp"
#include <ctime>

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

HealthProfile::HealthProfile(HealthProfile const &src) {
	*this = src;
	return;
}

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

int					HealthProfile::getWeight(void) const {
	return this->_weight;
}

int					HealthProfile::getHeight(void) const {
	return this->_height;
}

bool         		HealthProfile::setFirstName(std::string firstName) {
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
	if (yOB < 1 || yOB > 31)
		return false;
	this->_yOB = yOB;
	return true;
}

bool          		HealthProfile::setWeight(int weight) {
	if (weight < 1 || weight > INT_MAX)
		return false;
	this->_weight = weight;
	return true;
}

bool          		HealthProfile::setHeight(int height) {
	if (height < 1 || height > INT_MAX)
		return false;
	this->_height = height;
	return true;
}

int					HealthProfile::calculateAge(void) const {
	time_t now = time(0);
	tm *ltm = localtime(&now);
	int curYear = 1900 + ltm->tm_year;
	int curMon = 1 + ltm->tm_mon;
	int curDay = ltm->tm_mday;
	int age = curYear - this->_yOB - 1;

	if (curMon >= this->_mOB) {
		if (curMon == this->_mOB) {
			if (curDay >= this->_dOB) age++;
		} else {
			age++;
		}
	}
	return age;
}

int           		HealthProfile::calculateBMI(void) const {
	return 0;
}

int           		HealthProfile::calculateTHR(void) const {
	return 0;
}

std::ostream	&operator<<(std::ostream &o, HealthProfile const &i) {
	o << i.getFirstName() << " " << i.getLastName() << "'s health profile." << std::endl;
	o << "Date of Birth: " << i.getMOB() << "/" << i.getDOB() << "/" << i.getYOB() << std::endl;
	o << "Age: " << i.calculateAge() << std::endl;
	o << "Gender: " << i.getGender() << std::endl;
	o << "Weight: " << i.getWeight() << " -- Height: " << i.getHeight();
	return o;
}
