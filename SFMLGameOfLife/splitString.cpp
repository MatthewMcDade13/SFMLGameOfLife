
#include "stdafx.h"
#include "splitString.h"
#include <sstream>

std::vector<std::string> splitString(const std::string& string, char delim)
{
	std::vector<std::string> strings;
	std::istringstream ss(string);
	std::string buffer;
	while (std::getline(ss, buffer, delim))
	{
		strings.push_back(buffer);
	}

	return std::move(strings);
}