#ifndef _H_EVENT_MANAGER_H_
#define _H_EVENT_MANAGER_H_
#include "Event.hpp"
#include <vector>
#include <unordered_map>

typedef void (*EventListenerFunction)(Event e);
typedef std::vector<EventListenerFunction> EventListenerFunctions;
typedef std::unordered_map<EventType, EventListenerFunctions> EventListeners;

class EventManager {
    EventListeners listeners;
    public:
    EventManager() {};
    void addEventListener(EventType eventType, EventListenerFunction func);
    void dispatchEvent(Event event);
};

void EventManager::addEventListener(EventType eventType, EventListenerFunction func) {
    listeners[eventType].push_back(func);
}

void EventManager::dispatchEvent(Event event) {
    for (EventListenerFunction func : listeners[event.type()]) {
        (*func)(event);
    }
}


#endif // _H_EVENT_MANAGER_H_