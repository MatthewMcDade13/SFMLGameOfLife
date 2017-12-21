#include "stdafx.h"
#include "StringToCase.h"
#include <algorithm>

using std::string;
using std::transform;

string stringToUpper(const string& str)
{
	string cpy(str);

	transform(cpy.begin(), cpy.end(), cpy.begin(), ::toupper);

	return std::move(cpy);
}

string stringToLower(const string& str)
{
	string cpy(str);

	transform(cpy.begin(), cpy.end(), cpy.begin(), ::tolower);

	return std::move(cpy);
}
