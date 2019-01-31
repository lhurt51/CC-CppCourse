#ifndef HEALTHPROFILE_CLASS_HPP
# define HEALTHPROFILE_CLASS_HPP

#include <includes.hpp>

enum class Gender{ MALE, FEMALE, OTHER };

class HealthProfile {

  std::string const _firstName;
  std::string const _lastName;
  Gender const      _gender;

public:


  HealthProfile();
  HealthProfile(HealthProfile const &src);

}

#endif
