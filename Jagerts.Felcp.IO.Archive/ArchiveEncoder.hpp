#pragma once

#include "Jagerts.Felcp.Shared/Common.hpp"
#include "Jagerts.Felcp.IO/EncoderBase.hpp"

namespace Jagerts::Felcp::IO::Archive
{
	class ArchiveFile;
	
	class JAGERTS_FELCP_IO_ARCHIVE_API ArchiveEncoder : public StreamPathEncoder<ArchiveFile*, void*>
	{
	public:
		bool TryEncode(std::ostream& source, ArchiveFile* input, void* arg = NULL);
        using StreamPathEncoder::TryEncode;
	};
}