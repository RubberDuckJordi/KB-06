#include "LoggerPool.h"
#include "Logger.h"

namespace pengine
{
	LoggerPool::LoggerPool()
	{
		defaultLogFile = "PEngine";
		logExtension = ".log";
	}

	LoggerPool::~LoggerPool()
	{
		for (auto it = pool.begin(); it != pool.end(); ++it)
		{
			delete (*it).second;
		}
	}

	LoggerPool& LoggerPool::GetInstance()
	{
		static LoggerPool instance;
		return instance;
	}

	Logger* LoggerPool::GetLogger()
	{
		return GetLogger(defaultLogFile);
	}

	Logger* LoggerPool::GetLogger(std::string fileName)
	{
		for (auto poolItem : pool)
		{
			if (poolItem.first == fileName)
			{
				return poolItem.second;
			}
		}
		Logger* newLogger = new Logger(fileName + logExtension);
		pool[fileName] = newLogger;
		return newLogger;
	}

}