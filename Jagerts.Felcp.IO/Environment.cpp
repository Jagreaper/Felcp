#include "Environment.hpp"

using namespace Jagerts::Felcp::IO::Environment;

std::string _home;
bool _home_exists = false;

std::string GetHome()
{
    if (!_home_exists)
    {
        _home_exists = true;
        _home = getenv("HOME");
    }

    return _home;
}

std::string GetPath(const EnvironmentFolder folder)
{
    switch (folder)
    {
    case EnvironmentFolder::Home:
        return GetHome();
    case EnvironmentFolder::Documents:
        return GetHome() + "/Documents";
    case EnvironmentFolder::Desktop:
        return GetHome() + "/Desktop";
    case EnvironmentFolder::Pictures:
        return GetHome() + "/Pictures";
    case EnvironmentFolder::Movies:
        return GetHome() + "/Movies";
    case EnvironmentFolder::Music:
        return GetHome() + "/Music";
    case EnvironmentFolder::Downloads:
        return GetHome() + "/Downloads";
    case EnvironmentFolder::Applications:
#if (defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__))
        return GetHome() + "/Applications";
#elif defined(OSX)
        return GetHome() + "/AppData";
#endif
    default:
        throw std::runtime_error("Environment folder does not exist or support is not implemented for it");
    }
}