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
		if (pool.size() == 0){
			RemoveLogs(); // Remove the old logs whenever the first one is called
		}
		for (auto poolItem : pool)
		{
			if (poolItem.first == fileName)
			{
				return poolItem.second;
			}
		}
		Logger* newLogger = new Logger(fileName+logExtension);
		pool[fileName] = newLogger;
		return newLogger;
	}

	void LoggerPool::RemoveLogs()
	{
		std::string command = "del /Q ";
		std::string path = "*" + logExtension;
		system(command.append(path).c_str()); // Dangerous code.. Should be changed
	}

}