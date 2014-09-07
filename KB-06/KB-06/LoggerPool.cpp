#include "LoggerPool.h"
#include "Logger.h"

Logger::LoggerPool& Logger::LoggerPool::GetInstance(){
	static LoggerPool instance;
	return instance;
}

Logger::Logger* Logger::LoggerPool::GetLogger(){
	if (pool.empty()){
		return new Logger();
	}
	else {
		Logger* logger = pool.front();
		pool.pop_front();
		return logger;
	}
}

void Logger::LoggerPool::ReturnLogger(Logger* logger){
	logger->Reset();
	pool.push_back(logger);
}