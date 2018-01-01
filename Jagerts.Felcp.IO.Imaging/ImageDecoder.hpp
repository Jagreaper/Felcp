#pragma once

#include "Jagerts.Felcp.Shared\Common.hpp"
#include "Jagerts.Felcp.IO\DecoderBase.hpp"

namespace Jagerts::Felcp::Imaging
{
	class Image;
}

namespace Jagerts::Felcp::IO
{
	class JAGERTS_FELCP_IO_IMAGING_API ImagePathDecoder : public DecoderBase<const char*, Jagerts::Felcp::Imaging::Image*, void*>
	{
	public:
		bool TryDecode(const char* source, Jagerts::Felcp::Imaging::Image* output, void* arg);
	};
}