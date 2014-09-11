#ifndef _STRINGHELPER_H_
#define _STRINGHELPER_H_
#include <vector>
#include <string>
class StringHelper
{
	public:
	static std::vector<std::string> split(std::string &s, char delim);
	static std::vector<std::string> split(const std::string &s, char delim, std::vector<std::string> &elems);
	static bool EndsWith(std::string const &fullString, std::string const &ending);
};
#endif