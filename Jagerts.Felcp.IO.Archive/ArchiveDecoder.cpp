#include "ArchiveDecoder.hpp"
#include "ArchiveFile.hpp"
#include "ArchiveFileItem.hpp"

using namespace Jagerts::Felcp::IO::Archive;

#define _GET(TYPE, VAR) TYPE VAR; source >> VAR

bool ArchiveDecoder::TryDecode(std::istream& source, ArchiveFile* output, void* arg)
{
    _GET(int, name);
    _GET(int, version);
    _GET(size_t, file_count);

    std::vector<size_t> offsets;
    size_t b_offset = (sizeof(int) * 2) + sizeof(size_t);

    ArchiveFileItem** files = new ArchiveFileItem*[file_count];
    for (size_t index = 0; index < file_count; index++)
    {
        char* buffer;
        _GET(size_t, name_size);

        buffer = new char[name_size];
        source.get(buffer, name_size);
        std::string name = buffer;
        delete[] buffer;

        _GET(size_t, ext_size);

        buffer = new char[ext_size];
        source.get(buffer, ext_size);
        std::string ext = buffer;
        delete[] buffer;

        _GET(size_t, offset);
        offsets.push_back(offset);

        _GET(size_t, length);

        ArchiveFileItem* file = ArchiveFileItem::Create(length);
        file->SetName(name);
        file->SetExtension(ext);
        files[index] = file;

        b_offset += (sizeof(size_t) * 4) + name_size + ext_size;
    }

    for (size_t index = 0; index < file_count; index++)
    {
        size_t pos = b_offset + offsets[index];
        source.seekg(pos);

        size_t size = files[index]->GetSize();
        char* buffer = files[index]->GetData();
        source.get(buffer, size);

        output->AddFile(ArchiveFileItemType::Managed, files[index]);
    }

    delete[] files;
    return true;
}

#undef _GET