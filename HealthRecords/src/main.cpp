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
    HealthProfile newProf = HealthProfile("Liam", "Hurt", "M", 5, 2, 1998, 150, 71);

    std::cout << newProf << std::endl;
    return 0;
}
