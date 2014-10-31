#ifndef _PENGINE_LOGGER_H_
#define _PENGINE_LOGGER_H_

#include <string>
#include <windows.h>
#include <map>
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>

/*
System logger, can be used for debugging purposes
Logger can be retrieved from the LoggerPool.

Do NOT directly instaniate this class, use the loggerpool instead!
The logger defaults to the highest loglevel

*/

namespace pengine 
{
	class Logger
	{
	public:
		static enum LogLevel
		{
			NONE = 0,
			ERR = 1,
			WARNING = 2,
			DEBUG = 3,
			INFO = 4
		};

		// Initialises the logger with a file to write to
		// fileName must be given without the extension.
		Logger(std::string fileName);
		~Logger();

		void Log(int logType, std::string text);
		void SetLogLevel(int logLevel);

	private:
		void PrintConsole(int logType, std::string entry);
		// Transforms the message to a log entry, adds metadata such as logtype and timestamp.
		std::string BuildLogEntry(int logType, std::string messasge);

		std::ofstream outfile;
		int logLevel;
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
}
#endif