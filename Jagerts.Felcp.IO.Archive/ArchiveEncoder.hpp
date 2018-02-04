#pragma once

#include "Jagerts.Felcp.IO/EncoderBase.hpp"
#include "Archive.hpp"

namespace Jagerts::Felcp::IO::Archive
{
	class ArchiveEncoder : public StreamPathEncoder<Archive*, void*>
	{
	public:
		bool TryEncode(std::ostream& source, Archive* input, void* arg = NULL);
        using StreamPathEncoder::TryEncode;
	};
}