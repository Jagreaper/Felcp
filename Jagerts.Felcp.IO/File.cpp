#include "File.hpp"

using namespace Jagerts::Felcp::IO;

File::File(const std::string& path)
{
	this->_path = path;
}

const bool File::Exists() const
{
	std::ifstream stream(this->_path, std::ifstream::in);
	bool success = !(!stream);
	stream.close();
	return success;
}

void File::Create()
{
	std::ofstream stream(this->_path, std::ofstream::out | std::ofstream::trunc);

	if(!stream)
		throw std::runtime_error("File does not exists");

	stream.close();
}

const size_t File::GetSize() const
{
	std::ifstream stream(this->_path, std::ifstream::in);

	if(!stream)
		throw std::runtime_error("File does not exists");

	stream.seekg(0, stream.end);
	size_t size = stream.tellg();
	stream.close();
	
	return size;
}

void File::ReadAll(char* data, size_t* length_ptr) const
{
	std::ifstream stream(this->_path, std::ifstream::binary);

	if (!stream)
		throw std::runtime_error("File does not exists");

	stream.seekg(0, stream.end);
	size_t size = stream.tellg();

	stream.seekg(0, stream.beg);
	stream.read(data, size);

	stream.close();

	if (length_ptr != NULL)
		*length_ptr = size;
}

const char* File::ReadAll(size_t* length_ptr) const
{
	size_t size = this->GetSize();
	char* data = new char[size + 1];
	data[size] = '\0';

	this->ReadAll(data, length_ptr);
	return data;
}

void File::FreeData(const char*& data)
{
	delete[] data;
	data = NULL;
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