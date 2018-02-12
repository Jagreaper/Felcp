#include "ArchiveFileItem.hpp"
#include "ArchiveFile.hpp"

using namespace Jagerts::Felcp::IO::Archive;

ArchiveFile::~ArchiveFile()
{
    for (size_t index = 0; index < this->_managed_files.size(); index++)
        ArchiveFileItem::Free(this->_managed_files[index]);

    this->_managed_files.clear();
}

void ArchiveFile::AddFile(const ArchiveFileItemType type, const ArchiveFileItem* file)
{
    switch (type)
    {
    case ArchiveFileItemType::Managed:
        this->_managed_files.push_back(file);
    case ArchiveFileItemType::Unmanaged:
        this->_files.push_back(file);
        break;
    default:
        throw std::runtime_error("Invalid ArchiveFileItemType");
    }
}

void ArchiveFile::AddFiles(const ArchiveFileItemType type, const ArchiveFileItem* files, size_t size)
{
    for (size_t index = 0; index < size; index++)
        this->AddFile(type, files + (unsigned int)index);
}

void ArchiveFile::AddFiles(const ArchiveFileItemType type, const std::vector<ArchiveFileItem*>& files)
{
    for (size_t index = 0; index < files.size(); index++)
        this->AddFile(type, files[index]);
}

const ArchiveFileItem* ArchiveFile::GetFile(size_t index) const
{
    return this->_files[index];
}

const size_t ArchiveFile::GetFileCount() const
{
    return this->_files.size();
}