#include "EventManager.h"

EventManager::EventManager()
{
}

EventManager::~EventManager()
{
}

void EventManager::CreateEvent(std::string name) {
	if (!events.count(name))
	{
		events[name] = new Event(name);
	}
}

void EventManager::Subscribe(std::string name, EventListener* listener) {
	if (events.count(name))
	{
		events[name]->AddListener(listener);
	}
}

void EventManager::Proc(std::string name)
{
	if (events.count(name))
	{
		events[name]->Proc();
	}
}
