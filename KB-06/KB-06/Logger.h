#pragma once
#include <string>
#include <windows.h>
#include <map>
class Logger
{
public:
	~Logger();
	static enum LogLevel{
		NONE = 0,
		ERR = 1,
		WARNING = 2,
		DEBUG = 3,
		INFO = 4
	};

	static Logger* GetLogger(std::string text);
	void Log(int logType, std::string text);
	void SetLogLevel(int logLevel);
private:
	Logger();

	static std::map<std::string, Logger*> pool;
	void PrintConsole(int logType, std::string text);
	std::string BuildLogEntry(int logType, std::string messasge);

	int logLevel = 4;
	int consoleColorCodeInfo = gray;
	int consoleColorCodeDebug = white;
	int consoleColorCodeWarning = yellow;
	int consoleColorCodeError = red;

	HANDLE consoleHandle;

	enum Consolecolor
	{
		black = 0,
		dark_blue = 1,
		dark_green = 2,
		dark_aqua, dark_cyan = 3,
		dark_red = 4,
		dark_purple = 5, dark_pink = 5, dark_magenta = 5,
		dark_yellow = 6,
		dark_white = 7,
		gray = 8,
		blue = 9,
		green = 10,
		aqua = 11, cyan = 11,
		red = 12,
		purple = 13, pink = 13, magenta = 13,
		yellow = 14,
		white = 15
	};
};