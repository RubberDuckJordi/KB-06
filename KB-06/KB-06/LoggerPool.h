#ifndef _PENGINE_LOGGERPOOL_H_
#define _PENGINE_LOGGERPOOL_H_

#include "logger.h"
#include <list>

namespace pengine
{
	class LoggerPool
	{
	public:
		~LoggerPool();

		static LoggerPool& GetInstance();
		Logger* GetLogger();
		Logger* GetLogger(std::string fileName);
	private:
		LoggerPool();
		void LoggerPool::RemoveLogs();

		std::map<std::string, Logger*> pool;
		std::string defaultLogFile;
		std::string logExtension;
	};
}
#endif