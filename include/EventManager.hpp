#ifndef _H_EVENT_MANAGER_H_
#define _H_EVENT_MANAGER_H_
#include "Event.hpp"

class EventManager {
    public:
    EventManager() {};
    void addEventListener(EventType eventType);
    void dispatchEvent(Event event);
};

#endif // _H_EVENT_MANAGER_H_