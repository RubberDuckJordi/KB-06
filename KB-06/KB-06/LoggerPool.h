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
		void ReturnLogger(Logger* logger);
	private:
		LoggerPool();
		LoggerPool(LoggerPool const&);
		void operator=(LoggerPool const&);
		std::list<Logger*> pool;
	};
}
#endif