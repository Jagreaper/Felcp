#include "ArchiveEncoder.hpp"
#include "ArchiveFile.hpp"
#include "ArchiveFileItem.hpp"

using namespace Jagerts::Felcp::IO::Archive;

template<class T>
void _write_bin(std::ostream& source, T value)
{
	source.write(reinterpret_cast<const char*>(&value), sizeof(T));
}

bool ArchiveEncoder::TryEncode(std::ostream& source, ArchiveFile* input, void* arg)
{
    source << "ARCJ0000";
    _write_bin(source, input->GetFileCount());

    size_t offset = 0;
    for (size_t index = 0; index < input->GetFileCount(); index++)
    {
        const ArchiveFileItem* file = input->GetFile(index);
		_write_bin(source, file->GetName().size());
        source << file->GetName();
		_write_bin(source, file->GetExtension().size());
        source << file->GetExtension();
		_write_bin(source, offset);
		_write_bin(source, (offset += file->GetSize()));
    }

    for (size_t index = 0; index < input->GetFileCount(); index++)
    {
        const ArchiveFileItem* file = input->GetFile(index);
        source.write(file->GetData(), file->GetSize());
    }

    return true;
}