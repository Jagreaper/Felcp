#pragma once

#include "Jagerts.Felcp.Shared/Common.hpp"
#include <string>
#include <fstream>

namespace Jagerts::Felcp::IO
{
	class JAGERTS_FELCP_IO_API File
	{
	public:
		File(const std::string path);
		File(const std::string& path);
		const bool Exists() const;
		void Create();
#define OPEN_STREAM(STREAM_TYPE, STREAM_ARGS) \
		void OpenStream(STREAM_TYPE* stream, int mode = STREAM_ARGS); \

		OPEN_STREAM(std::ifstream, std::ifstream::in | std::ifstream::app)
		OPEN_STREAM(std::ofstream, std::ofstream::out | std::ofstream::trunc)
		OPEN_STREAM(std::fstream, std::fstream::in | std::fstream::out | std::fstream::app)
#undef OPEN_STREAM
	private:
		std::string _path;
	};
}