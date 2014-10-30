#include "Logger.h"

#include <iostream>
#include <sstream>
#include <windows.h>
#include <ctime>
#include <iomanip>

/*
Do NOT directly instaniate this class, use the loggerpool instead!
The logger defaults to the highest loglevel
*/

namespace pengine
{
	Logger::Logger(std::string fileName)
	{
		consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
		logLevel = INFO;
		outfile.open(fileName, std::ios_base::app);
	}

	Logger::~Logger()
	{
		outfile.close();
	}

	void Logger::Log(int logType, std::string messageString)
	{
		if (logLevel >= logType && logType > 0)
		{
			std::string entry = BuildLogEntry(logType, messageString);
			PrintConsole(logType, entry);
			outfile << entry << "\n";
			outfile.flush();
		}
	}

	void Logger::PrintConsole(int logType, std::string message)
	{
		int color;
		switch (logType) {
		case INFO:
			color = gray;
			break;
		case DEBUG:
			color = white;
			break;
		case WARNING:
			color = yellow;
			break;
		case ERR:
			color = red;
			break;
		default:
			color = 15;
			break;
		}
		SetConsoleTextAttribute(consoleHandle, color);

		std::cout << message << std::endl;
	}

	void Logger::SetLogLevel(int newLogLevel)
	{
		logLevel = newLogLevel;
	}

	std::string Logger::BuildLogEntry(int logType, std::string message)
	{
		std::stringstream logEntry;
		SYSTEMTIME systemTime;
		GetLocalTime(&systemTime);
		logEntry << "["
			<< std::setfill('0') << std::setw(2) << systemTime.wHour
			<< ":"
			<< std::setfill('0') << std::setw(2) << systemTime.wMinute
			<< ":"
			<< std::setfill('0') << std::setw(2) << systemTime.wSecond
			<< "."
			<< std::right << std::setfill('0') << std::setw(3) << systemTime.wMilliseconds
			<< "] ";

		logEntry << std::left << std::setfill(' ') << std::setw(8);
		switch (logType) {
		case INFO:
			logEntry << "INFO";
			break;
		case DEBUG:
			logEntry << "DEBUG";
			break;
		case WARNING:
			logEntry << "WARNING";
			break;
		case ERR:
			logEntry << "ERROR";
			break;
		}
		logEntry << message;
		return logEntry.str();
	}

	
}