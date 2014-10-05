#include "LoggerPool.h"
#include "Logger.h"

namespace pengine
{
	LoggerPool& LoggerPool::GetInstance()
	{
		static LoggerPool instance;
		return instance;
	}

	Logger* LoggerPool::GetLogger(){
		
		if (pool.empty())
		{
			return new Logger();
		}
		else
		{
			//Logger* logger = pool.front();
			//pool.pop_front();temp fix
			return pool.front();//temp fix
		}
	}

	void LoggerPool::ReturnLogger(Logger* logger)
	{
		logger->Reset();
		pool.push_back(logger);
	}
}