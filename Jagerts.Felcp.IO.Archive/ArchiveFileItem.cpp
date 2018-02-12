#include "ArchiveFileItem.hpp"

using namespace Jagerts::Felcp::IO::Archive;

ArchiveFileItem* ArchiveFileItem::Create(size_t size)
{
    return new ArchiveFileItem(size);
}

void ArchiveFileItem::Free(const ArchiveFileItem* const file)
{
    delete file;
}

ArchiveFileItem::ArchiveFileItem(size_t size)
{
    this->_data = new char[size];
    this->_size = size;
}

ArchiveFileItem::~ArchiveFileItem()
{
    delete[] this->_data;    
}

void ArchiveFileItem::SetName(const std::string& name)
{
    this->_name = name;
}

void ArchiveFileItem::SetExtension(const std::string& extension)
{
    this->_extension = extension;
}

const std::string& ArchiveFileItem::GetName() const
{
    return this->_name;
}

const std::string& ArchiveFileItem::GetExtension() const
{
    return this->_extension;
}

const char* ArchiveFileItem::GetData() const
{
    return this->_data;
}

char* ArchiveFileItem::GetData()
{
    return this->_data;
}

const size_t& ArchiveFileItem::GetSize() const
{
    return this->_size;
}
