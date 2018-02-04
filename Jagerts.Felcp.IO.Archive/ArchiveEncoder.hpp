#pragma once

#include "Jagerts.Felcp.Shared/Common.hpp"
#include "Jagerts.Felcp.IO/EncoderBase.hpp"

namespace Jagerts::Felcp::IO::Archive
{
	class Archive;
	
	class JAGERTS_FELCP_IO_ARCHIVE_API ArchiveEncoder : public StreamPathEncoder<Archive*, void*>
	{
	public:
		bool TryEncode(std::ostream& source, Archive* input, void* arg = NULL);
        using StreamPathEncoder::TryEncode;
	};
}