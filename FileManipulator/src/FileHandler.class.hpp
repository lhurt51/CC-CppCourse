#include <iostream>
#include <string>
#include <fstream>

class FileHandler
{

	enum ReadType
	{
		SAVE,
		RESTORE,
		DEFAULT,
	};

	static const std::string m_fileDir;
	static const std::string m_savedFileName;
	static const std::string m_readFileName;

	const ReadType m_readType;
	std::string m_wordToFind;


public:

	FileHandler(const ReadType readType = DEFAULT);
	FileHandler(const FileHandler& src);
	~FileHandler(void);

	FileHandler&	operator=(const FileHandler& rhs);

	// Class Getters
	ReadType 	GetReadType(void) const;

};
