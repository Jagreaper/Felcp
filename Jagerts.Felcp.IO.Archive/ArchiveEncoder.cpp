#include "ArchiveEncoder.hpp"
#include "ArchiveFile.hpp"

using namespace Jagerts::Felcp::IO::Archive;

bool ArchiveEncoder::TryEncode(std::ostream& source, Archive* input, void* arg)
{
    source << "ARCJ0000";
    source << input->GetFileCount();

    size_t offset = 0;
    for (size_t index = 0; index < input->GetFileCount(); index++)
    {
        const ArchiveFile* file = input->GetFile(index);
        source << file->GetName().size();
        source << file->GetName();
        source << file->GetExtension().size();
        source << file->GetExtension();
        source << offset;
        source << (offset += file->GetSize());
    }

    for (size_t index = 0; index < input->GetFileCount(); index++)
    {
        const ArchiveFile* file = input->GetFile(index);
        source.write(file->GetData(), file->GetSize());
    }

    return true;
}