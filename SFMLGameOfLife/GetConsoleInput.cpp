#include "stdafx.h"
#include "GetConsoleInput.h"
#include "StringToCase.h"

using namespace std;

string getConsoleInputstr(const string & message)
{
	string response;
	cout << message << ": ";
	cin >> response;
	return std::move(response);
}

bool getConsoleInputb(const string & message, const string & errorMessage)
{
	string response = "";
	string responseCpy = "";

	while(true)
	{
		cout << message << " (y/n): ";
		cin >> response;
		cout << endl;
		responseCpy = response;

		if (responseCpy.compare("yes") != 0 &&
			responseCpy.compare("no") != 0 &&
			responseCpy.compare("n") != 0 &&
			responseCpy.compare("y") != 0)
		{
			if (errorMessage.size() != 0)
				cout << errorMessage << endl;
		}
		else
		{
			break;
		}
	}

	if (response.compare("yes") == 0 || response.compare("y") == 0)
		return true;

	return false;
}

int getConsoleInputi(const string & message, const string & errorMessage)
{
	string response = "";
	bool bGoodParse = true;
	int result = 0;

	do
	{
		cout << message << ": ";
		cin >> response;
		cout << endl;

		try
		{
			result = std::stoi(response);
			bGoodParse = true;
		}
		catch (...)
		{
			bGoodParse = false;
			if (errorMessage.size() != 0)
				cout << errorMessage << endl;
		}

	} while (!bGoodParse);

	return result;
}

long getConsoleInputl(const string & message, const string & errorMessage)
{
	string response = "";
	bool bGoodParse = true;
	long result = 0;

	do
	{
		cout << message << ": ";
		cin >> response;
		cout << endl;

		try
		{
			result = std::stol(response);
			bGoodParse = true;
		}
		catch (...)
		{
			bGoodParse = false;
			if (errorMessage.size() != 0)
				cout << errorMessage << endl;
		}

	} while (!bGoodParse);


	return result;
}

long long getConsoleInputll(const string & message, const string & errorMessage)
{
	string response = "";
	bool bGoodParse = true;
	long long result = 0;

	do
	{
		cout << message << ": ";
		cin >> response;
		cout << endl;

		try
		{
			result = std::stoll(response);
			bGoodParse = true;
		}
		catch (...)
		{
			bGoodParse = false;
			if (errorMessage.size() != 0)
				cout << errorMessage << endl;
		}
	} while (!bGoodParse);


	return result;
}
