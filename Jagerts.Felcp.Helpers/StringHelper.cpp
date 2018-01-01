#include "StringHelper.hpp"
#include <cctype>

using namespace Kaleid::Helpers;

bool StringHelper::BeginsWith(const std::string& input, const std::string& match)
{
	return input.size() >= match.size() && std::equal(match.begin(), match.end(), input.begin());
}

bool StringHelper::EndsWith(const std::string& input, const std::string& match)
{
	return match.size() <= input.size() && std::equal(match.rbegin(), match.rend(), input.rbegin());
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
	for (int index = 0; index < s.length(); index++)
	{
		if (isspace(chars[index]) == 0)
			return std::string(chars);

		chars++;
	}
}