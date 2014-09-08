#include "stdafx.h"
#include "Logger.h"
#include <iostream>
#include <sstream>
#include <windows.h>
#include <ctime>
/*
Do NOT directly instaniate this class, use the loggerpool instead!
The logger defaults to the highest loglevel
*/

Logger::Logger::Logger()
{
	consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
}

void Logger::Logger::Reset(){
	logLevel = INFO;
}

void Logger::Logger::Log(int logType, std::string text){
	if (logLevel >= logType && logType > 0){
		std::string entry = BuildLogEntry(logType, text);
		PrintConsole(logType, entry);
		std::ofstream outfile;
		outfile.open("log.txt", std::ios_base::app);
		outfile << entry << "\n";
	}
}

void Logger::Logger::PrintConsole(int logType, std::string text)
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

	std::cout << text << std::endl;
}

void Logger::Logger::SetLogLevel(int newLogLevel){
	logLevel = newLogLevel;
}

std::string Logger::Logger::BuildLogEntry(int logType, std::string message){
	SYSTEMTIME systemTime;
	GetLocalTime(&systemTime);
	char* timeBuffer = new char[16];
	sprintf_s(timeBuffer, 16, "%02d:%02d:%02d.%03d", systemTime.wHour, systemTime.wMinute, systemTime.wSecond, systemTime.wMilliseconds);

	std::string logTypceString;
	switch (logType) {
		case INFO: logTypceString = "INFO   ";	break;
		case DEBUG:logTypceString = "DEBUG  "; break;
		case WARNING:logTypceString = "WARNING"; break;
		case ERR: logTypceString = "ERROR  "; break;
	}

	std::stringstream sstr;
	sstr << "[" << timeBuffer << "] " << logTypceString << ": " << message;
	delete[] timeBuffer;
	return sstr.str();
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