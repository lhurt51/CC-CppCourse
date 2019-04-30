#include <string>
#include <vector>
#include <sstream>
#include "DateConverter.class.hpp"

static std::vector<std::string>	split(const std::string& s, char const delimiter)
{
	std::vector<std::string> tokens;
   	std::string token;
   	std::istringstream tokenStream(s);

   	while (std::getline(tokenStream, token, delimiter))
   		tokens.push_back(token);
   	return tokens;
}

int main(int argc, char** argv)
{
    DateConverter dateConverter;

    if (argc == 1)
    {
        dateConverter.printDate();
    }
    else
    {
        std::vector<std::string> v;

        v = split(argv[1], '/');
        if (v.size() == 3)
        {
            try
            {
                dateConverter = DateConverter(std::stoi(v[1]), std::stoi(v[0]), std::stoi(v[2]));
                dateConverter.printDate();
            }
            catch(DateConverter::MonthOutOfRangeException& e)
            {
                std::cerr << e.what() << std::endl;
            }
            catch(DateConverter::DayOutOfRangeException& e)
            {
                std::cerr << e.what() << std::endl;
            }
        }
        else
        {
            std::cout << "Please formate date month/day/year" << std::endl;
        }
    }
	return 0;
}
