#include "stdafx.h"
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


pengine::Logger::Logger()
{
	consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
}

void pengine::Logger::Reset(){
	logLevel = INFO;
}

void pengine::Logger::NewFile(){
	remove(previousLogFile);
	rename(logFile, previousLogFile);
}
void pengine::Logger::Log(int logType, std::string messageString){
	char* message = new char[messageString.length() + 1];
	strcpy_s(message, messageString.length() + 1, messageString.c_str());
	Log(logType, message);
}

void pengine::Logger::Log(int logType, char* message){
	if (logLevel >= logType && logType > 0){
		std::string entry = BuildLogEntry(logType, message);
		PrintConsole(logType, entry);
		std::ofstream outfile;
		outfile.open(logFile, std::ios_base::app);
		outfile << entry << "\n";
	}
}

void pengine::Logger::PrintConsole(int logType, std::string message)
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

void pengine::Logger::SetLogLevel(int newLogLevel){
	logLevel = newLogLevel;
}

std::string pengine::Logger::BuildLogEntry(int logType, char* message){
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

	switch (logType) {
		case INFO: logEntry << "INFO   ";	break;
		case DEBUG:logEntry << "DEBUG  "; break;
		case WARNING: logEntry << "WARNING"; break;
		case ERR: logEntry << "ERROR  "; break;
	}
	logEntry << message;
	return logEntry.str();
}

void pengine::Logger::LogMemoryDump(int logType, void* const p_address, const int p_size, char* const p_name)
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