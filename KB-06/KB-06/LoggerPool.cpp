#include "LoggerPool.h"
#include "Logger.h"

pengine::LoggerPool& pengine::LoggerPool::GetInstance()
{
	static LoggerPool instance;
	return instance;
}

pengine::Logger* pengine::LoggerPool::GetLogger(){
	if (pool.empty())
	{
		return new Logger();
	}
	else
	{
		Logger* logger = pool.front();
		pool.pop_front();
		return logger;
	}
}

void pengine::LoggerPool::ReturnLogger(Logger* logger)
{
	logger->Reset();
	pool.push_back(logger);
}