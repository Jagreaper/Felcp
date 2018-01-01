#include "XmlEncoder.hpp"
#include <string>
#include <iostream>
#include <fstream>

using namespace Jagerts::Felcp::Xml;
using namespace Jagerts::Felcp::IO;
using namespace Jagerts::Felcp::IO::Xml;

bool XmlStreamEncoder::TryEncode(std::ostream& source, XmlFile* input, void* arg)
{
	std::string xml_string;
	input->ToString(&xml_string);
	source.write(xml_string.c_str(), xml_string.size());
	return true;
}

bool XmlPathEncoder::TryEncode(const char* source, XmlFile* input, void* arg)
{
	std::ofstream stream;
	stream.open(source, std::ofstream::out | std::ofstream::trunc);
	bool success = this->_stream_encoder.TryEncode(stream, input, NULL);
	stream.close();
	return success;
}