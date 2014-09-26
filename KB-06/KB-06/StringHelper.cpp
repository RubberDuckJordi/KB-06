#include "stdafx.h"
#include "StringHelper.h"

#include <sstream>

std::vector<std::string> pengine::StringHelper::split(std::string &s, char delim)
{
	std::vector<std::string> elems;
	split(s, delim, elems);
	return elems;
}

std::vector<std::string> pengine::StringHelper::split(const std::string &s, char delim, std::vector<std::string> &elems)
{
	std::stringstream ss(s);
	std::string item;
	while (std::getline(ss, item, delim))
	{
		elems.push_back(item);
	}
	return elems;
}

bool pengine::StringHelper::EndsWith(std::string const &fullString, std::string const &ending)
{
	if (fullString.length() >= ending.length())
	{
		return (0 == fullString.compare(fullString.length() - ending.length(), ending.length(), ending));
	}
	else
	{
		return false;
	}
}
