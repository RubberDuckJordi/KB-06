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
	Logger::Logger()
	{
		consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
		SetDefaultValues();
	}

	void Logger::Reset()
	{
		outfile.close();
		SetDefaultValues();
	}

	void Logger::SetDefaultValues()
	{
		logLevel = INFO;
		logFile = defaultLogFile;
	}

	void Logger::RemoveLogs()
	{
		std::string command = "del /Q ";
		std::string path = "*" + logExtension;
		system(command.append(path).c_str()); // Dangerous code.. Should be changed
	}

	void Logger::SetFile(std::string fileName)
	{
		logFile = fileName;
	}

	void Logger::Log(int logType, std::string messageString)
	{
		if (logLevel >= logType && logType > 0){
			std::string entry = BuildLogEntry(logType, messageString);
			PrintConsole(logType, entry);

			std::ofstream outfile; // needs to be reopened every time so multiple objects can use it
			outfile.open(logFile + logExtension, std::ios_base::app);
			outfile << entry << "\n";
			outfile.close();
		}
	}

	void Logger::PrintConsole(int logType, std::string message)
	{
		int color;
		switch (logType) {
		case INFO:
			color = consoleColorCodeInfo;
			break;
		case DEBUG:
			color = consoleColorCodeDebug;
			break;
		case WARNING:
			color = consoleColorCodeWarning;
			break;
		case ERR:
			color = consoleColorCodeError;
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
		case INFO: logEntry << "INFO";	break;
		case DEBUG:logEntry << "DEBUG"; break;
		case WARNING: logEntry << "WARNING"; break;
		case ERR: logEntry << "ERROR"; break;
		}
		logEntry << message;
		return logEntry.str();
	}

	void Logger::LogMemoryDump(int logType, void* const p_address, const int p_size, char* const p_name)
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
}