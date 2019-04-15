#include "FileHandler.class.hpp"

const std::string FileHandler::m_fileDir = "../res/";
const std::string FileHandler::m_savedFileName = "saved.txt";
const std::string FileHandler::m_readFileName = "input.txt";

FileHandler::FileHandler(const ReadType readType) : m_readType(readType)
{
	if (readType == DEFAULT) return;
}

FileHandler::FileHandler(const FileHandler& src) : m_readType(src.GetReadType())
{
	if (this != &src) { *this = src; }
}

FileHandler::~FileHandler(void)
{

}

FileHandler&	FileHandler::operator=(const FileHandler& rhs)
{
	if (this != &rhs) {}
	return *this;
}

FileHandler::ReadType 	FileHandler::GetReadType(void) const
{
	return m_readType;
}
