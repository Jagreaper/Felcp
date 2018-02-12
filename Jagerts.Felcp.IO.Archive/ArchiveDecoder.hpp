#pragma once

#include "Jagerts.Felcp.Shared/Common.hpp"
#include "Jagerts.Felcp.IO/DecoderBase.hpp"

namespace Jagerts::Felcp::IO::Archive
{
	class ArchiveFile;
	
	class JAGERTS_FELCP_IO_ARCHIVE_API ArchiveDecoder : public StreamPathDecoder<ArchiveFile*, void*>
	{
	public:
		bool TryDecode(std::istream& source, ArchiveFile* output, void* arg = NULL);
        using StreamPathDecoder::TryDecode;
	};
}