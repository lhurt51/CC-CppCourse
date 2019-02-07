#ifndef HEALTHPROFILE_CLASS_HPP
# define HEALTHPROFILE_CLASS_HPP

#include <includes.hpp>

class HealthProfile {

  // Private class attributes
  std::string   _firstName, _lastName, _gender;
  int           _dOB, _mOB, _yOB;
  int           _weight, _height;

public:

  // Constructors
  HealthProfile(std::string firstName, std::string lastName, std::string gender, int dOB, int mOB, int yOB, int weight, int height);
  HealthProfile(HealthProfile const &src);

  // Equal sign overload
  HealthProfile &operator=(HealthProfile const &rhs);

  // Getters
  std::string   getFirstName(void) const;
  std::string   getLastName(void) const;
  std::string   getGender(void) const;
  int           getDOB(void) const;
  int           getMOB(void) const;
  int           getYOB(void) const;
  int           getWeight(void) const;
  int           getHeight(void) const;

  // Setters
  bool          setFirstName(std::string firstName);
  bool          setLastName(std::string lastName);
  bool          setGender(std::string gender);
  bool          setDOB(int dOB);
  bool          setMOB(int mOB);
  bool          setYOB(int yOB);
  bool          setWeight(int weight);
  bool          setHeight(int height);

  // Calculation Methods
  int           calculateAge(void) const;
  int           calculateMHR(void) const;
  std::string   calculateTHR(void) const;
  float         calculateBMI(void) const;
  std::string   printBMIVal(void) const;

};

// Output overload
std::ostream    &operator<<(std::ostream &o, HealthProfile const &i);

#endif
