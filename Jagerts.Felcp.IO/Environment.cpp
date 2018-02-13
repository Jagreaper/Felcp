#include "Environment.hpp"
#include "Jagerts.Felcp.Helpers/StringHelper.hpp"

using namespace Jagerts::Felcp::Helpers;
using namespace Jagerts::Felcp::IO;

std::string _home;
bool _home_exists = false;

#ifdef _WIN32
#include <Shlobj.h>

std::string GetHomeW()
{
	WCHAR path[MAX_PATH + 1];
	if (SUCCEEDED(SHGetFolderPathW(NULL, CSIDL_PROFILE, NULL, 0, path)))
	{
		std::wstring ws(path);
		std::string str(ws.begin(), ws.end());
		
		str = StringHelper::Replace(str, "\\", "/");

		return str;
	}
	else
		throw std::runtime_error("Cannot find user directory");
}

#endif

std::string GetHome()
{
	if (!_home_exists)
	{
		_home_exists = true;

#ifdef _WIN32
		_home = GetHomeW();
#else
		_home = getenv("HOME");
#endif
	}

	return _home;
}

std::string Environment::GetPath(const Environment::Directory directory)
{
    switch (directory)
    {
    case Environment::Directory::Home:
        return GetHome();
    case Environment::Directory::Documents:
        return GetHome() + "/Documents";
    case Environment::Directory::Desktop:
        return GetHome() + "/Desktop";
    case Environment::Directory::Pictures:
        return GetHome() + "/Pictures";
    case Environment::Directory::Movies:
#if _WIN32
		return GetHome() + "/Videos";
#else
		return GetHome() + "/Movies";
#endif
    case Environment::Directory::Music:
        return GetHome() + "/Music";
    case Environment::Directory::Downloads:
        return GetHome() + "/Downloads";
    case Environment::Directory::Applications:
#if defined(_WIN32)
        return GetHome() + "/Applications";
#elif defined(OSX)
        return GetHome() + "/AppData";
#endif
    default:
        throw std::runtime_error("Environment folder does not exist or support is not implemented for it");
    }
}