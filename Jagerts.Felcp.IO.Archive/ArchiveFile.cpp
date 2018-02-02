#include "ArchiveFile.hpp"

using namespace Jagerts::Felcp::IO::Archive;

ArchiveFile* const ArchiveFile::Create(size_t size)
{
    return new ArchiveFile(size);
}

void ArchiveFile::Free(const ArchiveFile* const file)
{
    delete file;
}

ArchiveFile::ArchiveFile(size_t size)
{
    this->_data = new char[size];
}

ArchiveFile::~ArchiveFile()
{
    delete[] this->_data;    
}

void ArchiveFile::SetName(const std::string& name)
{
    this->_name = name;
}

void ArchiveFile::SetExtension(const std::string& extension)
{
    this->_extension = extension;
}

const std::string& ArchiveFile::GetName() const
{
    return this->_name;
}

const std::string& ArchiveFile::GetExtension() const
{
    return this->_extension;
}

const char* ArchiveFile::GetData() const
{
    return this->_data;
}

char* ArchiveFile::GetData()
{
    return this->_data;
}
