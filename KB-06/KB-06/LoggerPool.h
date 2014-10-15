#ifndef _PENGINE_LOGGERPOOL_H_
#define _PENGINE_LOGGERPOOL_H_

#include "logger.h"
#include <list>

namespace pengine
{
	class LoggerPool
	{
	public:
		static LoggerPool& GetInstance();
		Logger* GetLogger();
		Logger* GetLogger(std::string fileName);
	private:
		LoggerPool();
		LoggerPool(LoggerPool const&);
		void operator=(LoggerPool const&);
		std::map<std::string, Logger*> pool;
		std::string defaultLogFile = "PEngine";
		void LoggerPool::RemoveLogs();
		const std::string logExtension = ".log";
	};
}
#endif