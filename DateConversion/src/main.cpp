#include <string>
#include <vector>
#include <sstream>
#include "DateConverter.class.hpp"

union DateUnion
{
    struct
    {
        char month[2];
        char delimiter1;
        char day[2];
        char delimiter2;
        char year[4];
    } dateStruct;
    char dateData[10];
};

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
        //dateConverter = DateConverter();
        dateConverter.printDate();
    }
    else
    {
        std::vector<std::string> v;

        v = split(argv[1], '/');
        DateUnion dataUnion;
        strncpy(dataUnion.dateData, argv[1], 10);
        dataUnion.dateStruct.delimiter1 = '\0';
        dataUnion.dateStruct.delimiter2 = '\0';
        std::cout << dataUnion.dateStruct.month << std::endl;
        if (v.size() == 3)
        {
            dateConverter = DateConverter(std::stoi(v[1]), std::stoi(v[0]), std::stoi(v[2]));
            dateConverter.printDate();
        }
        else
        {
            std::cout << "Please formate date month/day/year" << std::endl;
        }
    }
	return 0;
}
