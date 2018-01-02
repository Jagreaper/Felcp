#pragma once

#include "Jagerts.Felcp.Shared\Common.hpp"
#include "Jagerts.Felcp.Xml\XmlFile.hpp"
#include "Jagerts.Felcp.IO\DecoderBase.hpp"

namespace Jagerts::Felcp::IO::Xml
{
	class JAGERTS_FELCP_IO_XML_API XmlDecoder : StreamPathDecoder<Jagerts::Felcp::Xml::XmlFile*, void*>
	{
	public:
		bool TryDecode(std::istream& source, Jagerts::Felcp::Xml::XmlFile* input, void* arg = NULL);
		using StreamPathDecoder::TryDecode;
	};
}
