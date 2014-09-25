#include "stdafx.h"
#include "Logger.h"

#include <iostream>
#include <sstream>
#include <windows.h>
#include <ctime>
#include <sstream>

/*
Do NOT directly instaniate this class, use the loggerpool instead!
The logger defaults to the highest loglevel
*/

Logger::Logger::Logger()
{
	consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
}

void Logger::Logger::Reset()
{
	logLevel = INFO;
}

void Logger::Logger::NewFile()
{
	remove(previousLogFile);
	rename(logFile, previousLogFile);
}

void Logger::Logger::Log(int logType, std::string messageString)
{
	char* message = new char[messageString.length() + 1];
	strcpy_s(message, messageString.length() + 1, messageString.c_str());
	Log(logType, message);
}

void Logger::Logger::Log(int logType, char* message)
{
	if (logLevel >= logType){
		std::ostringstream oss;

		SYSTEMTIME time;
		GetLocalTime(&time);

		char* logEntry = new char[16];
		sprintf_s(logEntry, 16, "[%02d:%02d:%02d.%03d] ", time.wHour, time.wMinute, time.wSecond, time.wMilliseconds);
		oss << logEntry;

		int color;
		switch (logType)
		{
		case INFO:
			oss << "<INFO   >: ";
			color = consoleColorCodeInfo;
			break;
		case DEBUG:
			oss << "<DEBUG  >: ";
			color = consoleColorCodeDebug;
			break;
		case WARNING:
			oss << "<WARNING>: ";
			color = consoleColorCodeWarning;
			break;
		case ERR:
			oss << "<ERROR  >: ";
			color = consoleColorCodeError;
			break;
		default:
			oss << "<NONE   >: ";
			color = consoleColorCodeNone;
			break;
		}

		oss << message << std::endl;

		if (!outfile.is_open())//We wouldn't want to open the file every single log, would we?
		{
			outfile.open("log.txt", std::ios_base::app);
			if (!outfile.is_open())
			{
				throw(std::runtime_error("LOGGER: can't open logfile!"));
			}
		}
		outfile << oss.str();
		outfile.flush();//Make sure every log is flushed, otherwise the log might not be there after a crash

		SetConsoleTextAttribute(consoleHandle, color);
		std::cout << oss.str();
	}
}

void Logger::Logger::SetLogLevel(int newLogLevel)
{
	logLevel = newLogLevel;
}

void Logger::Logger::LogMemoryDump(int logType, void* const p_address, const int p_size, char* const p_name)
{
	std::stringstream sstr;
	const char* c = reinterpret_cast<const char*>(p_address);

	sstr <<
		"MEMDUMP\t | " <<
		"N:[" << p_name << "]\t | " <<
		"A:[0x" << p_address << "]\t | " <<
		"S:" << p_size << " | " <<
		"D:[ ";

	for (int i = 0; i < p_size; ++i)
	{
		sstr << "0x" << std::hex << int(c[i]) << " ";
	}

	sstr << "]";
	Log(logType, sstr.str());
}

