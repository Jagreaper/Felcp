#include "ArchiveDecoder.hpp"
#include "ArchiveFile.hpp"
#include "ArchiveFileItem.hpp"

using namespace Jagerts::Felcp::IO::Archive;

#define _READ_S(NAME, BIN_SIZE) char NAME[BIN_SIZE]; source.read(NAME, BIN_SIZE)
#define _READ(TYPE, NAME) _READ_S(NAME##_s, sizeof(TYPE)); TYPE NAME = *reinterpret_cast<TYPE*>(NAME##_s);

bool ArchiveDecoder::TryDecode(std::istream& source, ArchiveFile* output, void* arg)
{
	_READ_S(name, 4);
	_READ_S(version, 4);
	_READ(size_t, file_count);

    std::vector<size_t> offsets;
    size_t b_offset = (sizeof(int) * 2) + sizeof(size_t);

    ArchiveFileItem** files = new ArchiveFileItem*[file_count];
    for (size_t index = 0; index < file_count; index++)
    {
        char* buffer;
		_READ(size_t, name_size);

        buffer = new char[name_size + 1];
		buffer[name_size] = '\0';
        source.read(buffer, name_size);
        std::string name = buffer;
        delete[] buffer;

		_READ(size_t, ext_size);

        buffer = new char[ext_size + 1];
		buffer[ext_size] = '\0';
        source.read(buffer, ext_size);
        std::string ext = buffer;
        delete[] buffer;

		_READ(size_t, offset);
        offsets.push_back(offset);

		_READ(size_t, length);

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
        source.read(buffer, size);

        output->AddFile(ArchiveFileItemType::Managed, files[index]);
    }

    delete[] files;
    return true;
}

#undef _READ_S
#undef _READ