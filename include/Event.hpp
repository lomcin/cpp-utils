#ifndef _H_EVENT_H_
#define _H_EVENT_H_

class Object;
class EventManager;

typedef enum EventTypeEnum {
    unknown = 0,
    onClick,
    onPress,
    onRelease,
    onChange,
    onFrame,
    onUpdate,
    onOpen,
    onClose
} EventType;

class Event {
    friend Object;
    friend EventManager;

    EventType m_type;
    EventManager* m_target = nullptr;

    public:

    Event(EventType type, EventManager* target) {
        m_type = type;
        m_target = target;
    }

    EventType type() {
        return m_type;
    }

    EventManager* target() {
        return m_target;
    }

};

#endif // _H_EVENT_H_