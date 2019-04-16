#include <iostream>
#include <string>
#include <fstream>

class FileHandler
{

public:

	enum ReadType
	{
		RESTORE,
		DEFAULT
	};

private:

	static const std::string m_fileDir;
	static const std::string m_savedFileName;
	static const std::string m_readFileName;

	const ReadType m_readType;
	const std::string m_wordToFind;
	std::string m_fileData;
	unsigned int m_dataIndex;
	unsigned int m_wordIndex;


public:

	FileHandler(const ReadType readType = DEFAULT, const std::string wordToFind = "cogswell");
	FileHandler(const FileHandler& src);
	~FileHandler(void);

	FileHandler&	operator=(const FileHandler& rhs);

	// Class Getters
	ReadType 	GetReadType(void) const;
	std::string GetWordToFind(void) const;
	std::string GetFileData(void) const;
	unsigned int GetDataIndex(void) const;
	unsigned int GetWordIndex(void) const;

	// Class helper methods
	void		ReadOneByte(void);
	bool		SaveRead(void);

private:

	

};
