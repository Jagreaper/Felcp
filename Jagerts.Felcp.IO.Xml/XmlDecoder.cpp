#include "XmlDecoder.hpp"

using namespace Jagerts::Felcp::Xml;
using namespace Jagerts::Felcp::IO::Xml;

bool XmlDecoder::TryDecode(std::istream& source, XmlFile* output, void* arg)
{
	std::string xml_str(std::istreambuf_iterator<char>(source), {});
	XmlFile::FromString(xml_str, output);
	return true;
}