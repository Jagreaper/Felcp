#include "StringHelper.hpp"
#include <cctype>

using namespace Jagerts::Felcp::Helpers;

bool StringHelper::BeginsWith(const std::string& input, const std::string& match)
{
	return input.size() >= match.size() && std::equal(match.begin(), match.end(), input.begin());
}

bool StringHelper::EndsWith(const std::string& input, const std::string& match)
{
	return match.size() <= input.size() && std::equal(match.rbegin(), match.rend(), input.rbegin());
}

bool StringHelper::Contains(const std::string& input, const std::string& match)
{
	return input.find(match) != std::string::npos;
}

std::string StringHelper::Replace(std::string string, const std::string& match, const std::string& replace)
{
	size_t index = 0;
	while ((index = string.find(match, index)) != std::string::npos)
	{
		string.replace(index, match.length(), replace);
		index += replace.length();
	}

	return string;
}

std::vector<std::string> StringHelper::Split(const std::string &s, char delim)
{
	std::vector<std::string> elems;
	StringHelper::Split(s, delim, std::back_inserter(elems));
	return elems;
}

std::string StringHelper::TrimLeading(const std::string& s)
{
	if (s.length() == 0)
		return s;

	const char* chars = s.c_str();
	for (unsigned int index = 0; index < (unsigned int)s.length(); index++)
	{
		if (isspace(chars[index]) == 0)
			return std::string(chars);

		chars++;
	}

	return s;
}