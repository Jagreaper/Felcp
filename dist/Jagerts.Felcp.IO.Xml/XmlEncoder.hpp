#pragma once

#include "Jagerts.Felcp.Shared\Common.hpp"
#include "Jagerts.Felcp.Xml\XmlFile.hpp"
#include "Jagerts.Felcp.IO\EncoderBase.hpp"

namespace Jagerts::Felcp::IO::Xml
{
	class JAGERTS_FELCP_IO_XML_API XmlEncoder : public StreamPathEncoder<Jagerts::Felcp::Xml::XmlFile*, void*>
	{
	public:
		bool TryEncode(std::ostream& source, Jagerts::Felcp::Xml::XmlFile* input, void* arg = NULL);
		using StreamPathEncoder::TryEncode;
	};
}