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

void Logger
::Logger::NewFile(){
	remove(previousLogFile);
	rename(logFile, previousLogFile);
}
void Logger::Logger::Log(int logType, std::string messageString){
	char* message = new char[messageString.length()+1];
	strcpy_s(message, messageString.length()+1, messageString.c_str());
	Log(logType, message);
}

void Logger::Logger::Log(int logType, char* message){
	if (logLevel >= logType && logType > 0){
		char* entry = BuildLogEntry(logType, message);
		PrintConsole(logType, entry);
		std::ofstream outfile;
		outfile.open("log.txt", std::ios_base::app);
		outfile << entry << "\n";
	}
}

void Logger::Logger::PrintConsole(int logType, char* message)
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

void Logger::Logger::SetLogLevel(int newLogLevel){
	logLevel = newLogLevel;
}

char* Logger::Logger::BuildLogEntry(int logType, char* message){
	SYSTEMTIME systemTime;
	GetLocalTime(&systemTime);
	char* logTypeString = new char[7];
	switch (logType) {
		case INFO: logTypeString = "INFO   ";	break;
		case DEBUG:logTypeString = "DEBUG  "; break;
		case WARNING:logTypeString = "WARNING"; break;
		case ERR: logTypeString = "ERROR  "; break;
	}
	char* logEntry = new char[240 + sizeof(message) + sizeof(logTypeString)];
	sprintf_s(logEntry, 240, "[%02d:%02d:%02d.%03d] %s %s", systemTime.wHour, systemTime.wMinute, systemTime.wSecond, systemTime.wMilliseconds, logTypeString, message);
	return logEntry;
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

