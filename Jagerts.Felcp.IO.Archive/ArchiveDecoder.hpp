#pragma once

#include "Jagerts.Felcp.Shared/Common.hpp"
#include "Jagerts.Felcp.IO/DecoderBase.hpp"

namespace Jagerts::Felcp::IO::Archive
{
	class Archive;
	
	class JAGERTS_FELCP_IO_ARCHIVE_API ArchiveDecoder : public StreamPathDecoder<Archive*, void*>
	{
	public:
		bool TryDecode(std::istream& source, Archive* output, void* arg = NULL);
        using StreamPathDecoder::TryDecode;
	};
}