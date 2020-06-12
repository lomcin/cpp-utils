#ifndef _H_EVENT_H_
#define _H_EVENT_H_

class Object;

typedef enum EventType {
    unknown = 0,
    onClick,
    onPress,
    onRelease,
    onChange,
    onFrame,
    onUpdate,
    onOpen,
    onClose
};

class Event {
    friend Object;

    EventType m_type;
    void* m_target = nullptr;

    public:

    Event(EventType type, void* target) {
        m_type = type;
        m_target = target;
    }

    EventType type() {
        return m_type;
    }

    void* target() {
        return m_target;
    }

};

#endif // _H_EVENT_H_