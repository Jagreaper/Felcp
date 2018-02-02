#include "ArchiveFile.hpp"
#include "Archive.hpp"

using namespace Jagerts::Felcp::IO::Archive;

Archive::~Archive()
{
    for (size_t index = 0; index < this->_managed_files.size(); index++)
        ArchiveFile::Free(this->_managed_files[index]);

    this->_managed_files.clear();
}

void Archive::AddFile(const ArchiveFileType type, const ArchiveFile* file)
{
    switch (type)
    {
    case ArchiveFileType::Managed:
        this->_managed_files.push_back(file);
    case ArchiveFileType::Unmanaged:
        this->_files.push_back(file);
        break;
    default:
        throw std::runtime_error("Invalid ArchiveFileType");
    }
}

void Archive::AddFiles(const ArchiveFileType type, const ArchiveFile* files, size_t size)
{
    for (size_t index = 0; index < size; index++)
        this->AddFile(type, files + (unsigned int)index);
}

void Archive::AddFiles(const ArchiveFileType type, const std::vector<ArchiveFile*>& files)
{
    for (size_t index = 0; index < files.size(); index++)
        this->AddFile(type, files[index]);
}

const ArchiveFile* Archive::GetFile(size_t index)
{
    return this->_files[index];
}

const size_t Archive::GetFileCount() const
{
    return this->_files.size();
}