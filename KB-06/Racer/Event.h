#pragma once
#include <string>
#include <vector>
#include "EventListener.h"
class Event
{
public:
	Event(std::string name);
	~Event();
	void Proc();
	void AddListener(EventListener* listener);
private:
	std::vector<EventListener*> listeners;
	std::string name;
};
