#include "File.hpp"
#include <fstream>

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