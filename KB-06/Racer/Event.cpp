#include "Event.h"


Event::Event(std::string eventName)
{
	name = eventName;
}

Event::~Event()
{
}

void Event::Proc(){
	for (auto & listener : listeners) {
		listener->ProcEvent(name);
	}
}

void Event::AddListener(EventListener* listener){
	listeners.push_back(listener);
}

void Event::RemoveListener(EventListener* listener){
	for (std::vector<EventListener*>::iterator it = listeners.begin(); it != listeners.end();) { // note the missing ++iter!; noted
		if ((*it) == listener)
		{
			delete *it;
			it = listeners.erase(it);
		}
		else {
			++it;
		}
	}
}