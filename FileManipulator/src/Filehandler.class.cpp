#include "FileHandler.class.hpp"

// Saving the files names as constants
const std::string FileHandler::m_fileDir = "../res/";
const std::string FileHandler::m_savedFileName = "saved.txt";
const std::string FileHandler::m_readFileName = "input.txt";

FileHandler::FileHandler(const ReadType readType, const std::string wordToFind) : m_readType(readType), m_wordToFind(wordToFind), m_dataIndex(0), m_wordIndex(0)
{
	std::string line;
    std::ifstream fin;

	// Opening a specific file based on the read type feed into the constructor
	switch(readType)
	{
		case RESTORE:
			fin.open(m_fileDir + m_savedFileName);
		case DEFAULT:
		default:
			fin.open(m_fileDir + m_readFileName);
			break;
	}

	// Check for open file
	if (fin.is_open())
	{
		if (readType == RESTORE)
		{
			std::cout << std::endl << "\tRESTORE THE GAME" << std::endl;
			std::cout << "\t----------------" << std::endl << std::endl;
			// I know its already open but I need to do this to get the ints
			fin.close();
			fin.open(m_fileDir + m_savedFileName, std::ios::in);
			fin >> m_dataIndex >> m_wordIndex;
			fin.close();
			fin.open(m_fileDir + m_savedFileName);
			fin.ignore(256, '`');
		}
		// Setting up the string to look through
		char c = fin.get();
		while (fin.good())
	    {
			m_fileData += c;
			c = fin.get();
	    }
		fin.close();
	}
}

FileHandler::FileHandler(const FileHandler& src) : m_readType(src.GetReadType()), m_wordToFind(src.GetWordToFind())
{
	*this = src;
}

FileHandler::~FileHandler(void)
{
	return;
}

FileHandler&			FileHandler::operator=(const FileHandler& rhs)
{
	if (this != &rhs)
	{
		this->m_fileData = rhs.GetFileData();
		this->m_dataIndex = rhs.GetDataIndex();
		this->m_wordIndex = rhs.GetWordIndex();
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

unsigned int 			FileHandler::GetDataIndex(void) const
{
	return m_dataIndex;
}

unsigned int 			FileHandler::GetWordIndex(void) const
{
	return m_wordIndex;
}

// Class helper methods
void					FileHandler::ReadOneByte(void)
{
	static bool finnished = false;

	// Check end conditions
	if (finnished) return;
	else if (m_wordIndex >= m_wordToFind.size())
	{
		finnished = true;
		std::cout << std::endl << "The word " + m_wordToFind + " was found!" << std::endl;
		return;
	}
	else if (m_dataIndex >= m_fileData.size())
	{
		finnished = true;
		std::cout << std::endl << "The word " + m_wordToFind + " was not found!" << std::endl;
		return;
	}

	// Check & print byte
	char c = m_fileData[m_dataIndex];

	if (c == m_wordToFind[0])
		m_wordIndex = 1;
	else if (c == m_wordToFind[m_wordIndex])
		m_wordIndex++;
	else if (c != '\n')
		c = '.';

	m_dataIndex++;
	if (c != '\n') std::cout << c << std::flush;
}

bool				FileHandler::SaveRead(void)
{
	std::string line;
	std::ofstream fout;

	fout.open(m_fileDir + m_savedFileName);
	if (fout.is_open())
	{
		fout << m_dataIndex << " " << m_wordIndex << "`" << m_fileData;
		std::cout << std::endl << "\tSAVE THE GAME" << std::endl;
		std::cout << "\t-------------" << std::endl << std::endl;
		fout.close();
		return true;
	}
	return false;
}
