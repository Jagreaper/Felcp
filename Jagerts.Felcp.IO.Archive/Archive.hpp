#pragma once

#include <vector>
#include <string>

namespace Jagerts::Felcp::IO::Archive
{
    class ArchiveFile;

    enum class ArchiveFileType
    {
        Managed,
        Unmanaged,
    };

    class Archive
    {
    public:
        ~Archive();
        void AddFile(const ArchiveFileType type, const ArchiveFile* file);
        void AddFiles(const ArchiveFileType type, const ArchiveFile* files, size_t size);
        void AddFiles(const ArchiveFileType type, const std::vector<ArchiveFile*>& files);

        const ArchiveFile* GetFile(size_t index) const;
        const size_t GetFileCount() const;
    private:
        std::vector<const ArchiveFile*> _files;
        std::vector<const ArchiveFile*> _managed_files;
    };
}