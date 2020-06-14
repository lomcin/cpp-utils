#ifndef _H_EVENT_MANAGER_H_
#define _H_EVENT_MANAGER_H_
#include "Event.hpp"
#include "BasicTypes.hpp"
#include <functional>

typedef void (*EventListenerFunctionC)(Event e);
#define EventListenerFunctionType void(Event e)
typedef std::function<EventListenerFunctionType> EventListenerFunction;
typedef std::vector<EventListenerFunction> EventListenerFunctions;
typedef std::unordered_map<EventType, EventListenerFunctions> EventListeners;

#define toFunction(function) static_cast<EventListenerFunction>([&](Event ___e___){function(___e___);})

class EventManager {
    EventListeners listeners;
    public:
    EventManager() {};
    template<typename EventListenerFunctionTypename>
    void addEventListener(EventType eventType, EventListenerFunctionTypename func);
    void dispatchEvent(Event event);
    void dispatchEvent(EventType eventType);
};

template<>
void EventManager::addEventListener(EventType eventType, EventListenerFunctionC func) {
    listeners[eventType].push_back(func);
}

template<typename EventListenerFunctionTypename>
void EventManager::addEventListener(EventType eventType, EventListenerFunctionTypename func) {
    listeners[eventType].push_back(func);
}

void EventManager::dispatchEvent(Event event) {
    for (EventListenerFunction func : listeners[event.type()]) {
        func(event);
    }
}

void EventManager::dispatchEvent(EventType eventType) {
    dispatchEvent(Event(eventType,this));
}

#endif // _H_EVENT_MANAGER_H_