#include <iostream>
#include <string>
#include <fstream>

class FileHandler
{

	static const std::string savedFileName = "savedText";
	std::string fileName;

public:

	FileHandler(const std::string& fileName);
	FileHandler(const FileHandler& src);
	~FileHandler(void);

	FileHandler&	operator=(const FileHandler& rhs);

};
