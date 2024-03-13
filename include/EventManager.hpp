/*
MIT License

Copyright (c) 2020-2024 Lucas Maggi

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#ifndef _H_EVENT_MANAGER_H_
#define _H_EVENT_MANAGER_H_
#include "Event.hpp"
#include <vector>
#include <unordered_map>
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