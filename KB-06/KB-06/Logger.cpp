#include "stdafx.h"
#include "Logger.h"
#include <iostream>
#include <sstream>
#include <windows.h>
#include <ctime>

Logger::Logger()
{
	consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
}

Logger::~Logger()
{
	//for (it_type iterator = m.begin(); iterator != m.end(); iterator++) {
		// iterator->first = key
		// iterator->second = value
		// Repeat if you also want to iterate through the second map.
	//}
}

Logger* Logger::GetLogger(std::string text){
	if (pool.find(text) != pool.end()){
		return pool[text];
	} 
	Logger* logger = new Logger;
	pool[text] = logger;
	return logger;
}

std::map<std::string, Logger*> Logger::pool;

void Logger::Log(int logType, std::string text){
	if (logLevel >= logType && logType > 0){		
		PrintConsole(logType, BuildLogEntry(logType, text));
	}
}

void Logger::PrintConsole(int logType,std::string text)
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

void Logger::SetLogLevel(int newLogLevel){
	logLevel = newLogLevel;
}

std::string Logger::BuildLogEntry(int logType, std::string message){
	SYSTEMTIME systemTime;
	GetLocalTime(&systemTime);
	char* timeBuffer = new char[15];
	sprintf_s(timeBuffer, 15, "%02d:%02d:%02d.%02d", systemTime.wHour, systemTime.wMinute, systemTime.wSecond, systemTime.wMilliseconds);

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