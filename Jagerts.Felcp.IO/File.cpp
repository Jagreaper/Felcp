#include "File.hpp"

using namespace Jagerts::Felcp::IO;

File::File(const std::string path)
{
	this->_path = path;
}

File::File(const std::string& path)
{
	this->_path = path;
}

const bool File::Exists() const
{
	std::ofstream stream(this->_path, std::ofstream::out | std::ofstream::app);
	bool success = !(!stream);
	stream.close();
	return success;
}

void File::Create()
{
	std::ofstream stream(this->_path, std::ofstream::out | std::ofstream::trunc);
	stream.close();
}

#define _OPEN_STREAM(STREAM_TYPE)\
void File::OpenStream(STREAM_TYPE* stream, int mode) \
{ \
	if (stream->is_open()) \
		stream->close(); \
	\
	stream->open(this->_path, mode); \
} \
\

_OPEN_STREAM(std::ifstream)
_OPEN_STREAM(std::ofstream)
_OPEN_STREAM(std::fstream)
#undef _OPEN_STREAM