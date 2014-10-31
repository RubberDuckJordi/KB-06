#ifndef _PENGINE_LOGGERPOOL_H_
#define _PENGINE_LOGGERPOOL_H_

#include "logger.h"
#include <list>

/*
Pool pattern

Is responsible for managing all loggers.
This pool is a singleton to make sure that it can be called from anywhere in the engine.
*/

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

		std::map<std::string, Logger*> pool;
		std::string defaultLogFile;
		std::string logExtension;
	};
}
#endif