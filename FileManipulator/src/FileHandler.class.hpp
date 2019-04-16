#include <iostream>
#include <string>
#include <fstream>

class FileHandler
{

	enum ReadType
	{
		RESTORE,
		DEFAULT
	};

	static const std::string m_fileDir;
	static const std::string m_savedFileName;
	static const std::string m_readFileName;

	const ReadType m_readType;
	std::string m_wordToFind;
	std::string m_fileData;
	unsigned int m_dataIndex;
	unsigned int m_wordIndex;


public:

	FileHandler(const ReadType readType = DEFAULT);
	FileHandler(const FileHandler& src);
	~FileHandler(void);

	FileHandler&	operator=(const FileHandler& rhs);

	// Class Getters
	ReadType 	GetReadType(void) const;
	std::string GetWordToFind(void) const;
	std::string GetFileData(void) const;

	// Class helper methods
	char		ReadOneByte(void);
	bool		SaveCurPos(void);

};
