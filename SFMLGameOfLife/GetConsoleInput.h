#pragma once
#include <string>

std::string getConsoleInputstr(const std::string& message);

bool getConsoleInputb(const std::string& message, const std::string& errorMessage = "");

int getConsoleInputi(const std::string& message, const std::string& errorMessage = "");

long getConsoleInputl(const std::string& message, const std::string& errorMessage = "");

long long getConsoleInputll(const std::string& message, const std::string& errorMessage = "");