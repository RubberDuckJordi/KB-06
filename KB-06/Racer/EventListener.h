#pragma once
#include <string>
class EventListener
{
public:
	virtual void ProcEvent(std::string eventName) = 0;
};