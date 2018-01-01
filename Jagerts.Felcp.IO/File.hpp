#pragma once

#include "Jagerts.Felcp.Shared\Common.hpp"
#include <string>

namespace Jagerts::Felcp::IO
{
	class JAGERTS_FELCP_IO_API File
	{
	public:
		File(const std::string path);
		File(const std::string& path);
		const bool Exists() const;
		void Create();
	private:
		std::string _path;
	};
}