#include "LoggerPool.h"
#include "Logger.h"

namespace pengine
{
	LoggerPool::LoggerPool()
	{
	}

	LoggerPool& LoggerPool::GetInstance()
	{
		static LoggerPool instance;
		return instance;
	}

	Logger* LoggerPool::GetLogger(){
		return GetLogger(defaultLogFile);
	}

	Logger* LoggerPool::GetLogger(std::string fileName){
		for (auto poolItem : pool)
		{
			if (poolItem.first == fileName)
			{
				return poolItem.second;
			}
		}
		Logger* newLogger = new Logger(fileName);
		pool[fileName] = newLogger;
		return newLogger;
	}
}