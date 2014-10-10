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