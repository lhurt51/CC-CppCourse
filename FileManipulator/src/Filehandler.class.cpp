#include "FileHandler.class.hpp"

const std::string FileHandler::m_fileDir = "../res/";
const std::string FileHandler::m_savedFileName = "saved.txt";
const std::string FileHandler::m_readFileName = "input.txt";

FileHandler::FileHandler(const ReadType readType) : m_readType(readType), m_dataIndex(0), m_wordIndex(0)
{
	std::string line;
    std::ifstream fin;

	switch(readType)
	{
		case RESTORE:
			fin.open(m_fileDir + m_savedFileName);
		case DEFAULT:
		default:
			fin.open(m_fileDir + m_readFileName);
			break;
	}

	while (fin)
    {
        getline(fin, line);
        std::cout << line << std::endl;
		m_fileData += line;
    }
    fin.close();
}

FileHandler::FileHandler(const FileHandler& src) : m_readType(src.GetReadType())
{
	*this = src;
}

FileHandler::~FileHandler(void)
{

}

FileHandler&			FileHandler::operator=(const FileHandler& rhs)
{
	if (this != &rhs)
	{
		this->m_wordToFind = rhs.GetWordToFind();
		this->m_fileData = rhs.GetFileData();
	}
	return *this;
}

FileHandler::ReadType 	FileHandler::GetReadType(void) const
{
	return m_readType;
}

std::string 			FileHandler::GetWordToFind(void) const
{
	return m_wordToFind;
}

std::string 			FileHandler::GetFileData(void) const
{
	return m_fileData;
}

// Class helper methods
char					FileHandler::ReadOneByte(void)
{
	if (m_dataIndex >= m_fileData.size()) return '\0';
	char print = m_fileData[m_dataIndex];
	m_dataIndex++;
	m_wordIndex++;
	return print;
}
