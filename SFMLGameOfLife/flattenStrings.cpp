#include "stdafx.h"
#include "flattenStrings.h"

std::string flattenStrings(const std::vector<std::string> strings)
{
	std::string newString = "";

	for (size_t i = 0; i < strings.size(); i++)
	{
		newString += strings[i];
	}

	return std::move(newString);
}