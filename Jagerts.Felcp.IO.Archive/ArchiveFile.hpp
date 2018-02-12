#pragma once

#include "Jagerts.Felcp.Shared/Common.hpp"
#include <vector>
#include <string>

namespace Jagerts::Felcp::IO::Archive
{
    class ArchiveFileItem;

    enum class ArchiveFileItemType
    {
        Managed,
        Unmanaged,
    };

    class JAGERTS_FELCP_IO_ARCHIVE_API ArchiveFile
    {
    public:
        ~ArchiveFile();
        void AddFile(const ArchiveFileItemType type, const ArchiveFileItem* file);
        void AddFiles(const ArchiveFileItemType type, const ArchiveFileItem* files, size_t size);
        void AddFiles(const ArchiveFileItemType type, const std::vector<ArchiveFileItem*>& files);

        const ArchiveFileItem* GetFile(size_t index) const;
        const size_t GetFileCount() const;
    private:
        std::vector<const ArchiveFileItem*> _files;
        std::vector<const ArchiveFileItem*> _managed_files;
    };
}