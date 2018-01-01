#pragma once

#include "Jagerts.Felcp.Shared\Common.hpp"
#include "Jagerts.Felcp.Xml\XmlFile.hpp"
#include "Jagerts.Felcp.IO\EncoderBase.hpp"

namespace Jagerts::Felcp::IO::Xml
{
	class JAGERTS_FELCP_IO_XML_API XmlStreamEncoder : StreamEncoderBase<Jagerts::Felcp::Xml::XmlFile*, void*>
	{
	public:
		bool TryEncode(std::ostream& source, Jagerts::Felcp::Xml::XmlFile* input, void* arg);
	};

	class JAGERTS_FELCP_IO_XML_API XmlPathEncoder : PathEncoderBase<Jagerts::Felcp::Xml::XmlFile*, void*>
	{
	public:
		bool TryEncode(const char* source, Jagerts::Felcp::Xml::XmlFile* input, void* arg);
	private:
		XmlStreamEncoder _stream_encoder;;
	};
}