#pragma once

#include "Jagerts.Felcp.Shared/Common.hpp"
#include <vector>
#include <string>

namespace Jagerts::Felcp::IO::Archive
{
    class JAGERTS_FELCP_IO_ARCHIVE_API ArchiveFileItem
    {
    public:
        static ArchiveFileItem* Create(size_t size);
        static void Free(const ArchiveFileItem* const file);
        void SetName(const std::string& name);
        void SetExtension(const std::string& extension);
        const std::string& GetName() const;
        const std::string& GetExtension() const;
        const char* GetData() const;
        char* GetData();
        const size_t& GetSize() const;
    private:
        ArchiveFileItem(size_t size);
        ~ArchiveFileItem();
        std::string _name;
        std::string _extension;
        char* _data = NULL;
        size_t _size;
    };
}