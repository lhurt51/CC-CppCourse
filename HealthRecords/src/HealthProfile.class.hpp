#ifndef HEALTHPROFILE_CLASS_HPP
# define HEALTHPROFILE_CLASS_HPP

#include <includes.hpp>

class HealthProfile {

  std::string   _firstName;
  std::string   _lastName;
  std::string   _gender;
  int           _dOB;
  int           _mOB;
  int           _yOB;
  int           _weight;
  int           _height;

public:

  HealthProfile(std::string firstName, std::string lastName, std::string gender, int dOB, int mOB, int yOB, int weight, int height);
  HealthProfile(HealthProfile const &src);

  HealthProfile &operator=(HealthProfile const &rhs);

  std::string   getFirstName(void) const;
  std::string   getLastName(void) const;
  std::string   getGender(void) const;
  int           getDOB(void) const;
  int           getMOB(void) const;
  int           getYOB(void) const;
  int           getWeight(void) const;
  int           getHeight(void) const;

  bool          setFirstName(std::string firstName);
  bool          setLastName(std::string lastName);
  bool          setGender(std::string gender);
  bool          setDOB(int dOB);
  bool          setMOB(int mOB);
  bool          setYOB(int yOB);
  bool          setWeight(int weight);
  bool          setHeight(int height);

  int           calculateAge(void) const;
  int           calculateBMI(void) const;
  int           calculateTHR(void) const;

};

std::ostream    &operator<<(std::ostream &o, HealthProfile const &i);

#endif
