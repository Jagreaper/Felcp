#pragma once

#include "Jagerts.Felcp.Shared/Common.hpp"
#include <string>

namespace Jagerts::Felcp::IO::Environment
{
    enum EnvironmentFolder
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

    std::string GetPath(const EnvironmentFolder folder);
}