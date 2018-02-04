#pragma once

#include "Jagerts.Felcp.IO/DecoderBase.hpp"
#include "Archive.hpp"

namespace Jagerts::Felcp::IO::Archive
{
	class ArchiveDecoder : public StreamPathDecoder<Archive*, void*>
	{
	public:
		bool TryDecode(std::istream& source, Archive* output, void* arg = NULL);
        using StreamPathDecoder::TryDecode;
	};
}