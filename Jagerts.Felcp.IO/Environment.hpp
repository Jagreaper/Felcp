#pragma once

#include "Jagerts.Felcp.Shared/Common.hpp"
#include <string>

namespace Jagerts::Felcp::IO::Environment
{
    enum Directory
    {
        Home,
        Documents,
        Desktop,
        Pictures,
        Movies,
        Music,
        Downloads,
        Applications,
    };

	JAGERTS_FELCP_IO_API std::string GetPath(const Directory directory);
}