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
    Object* m_target = nullptr;

    public:

    Event(EventType type, Object* target) {
        m_type = type;
        m_target = target;
    }

    template<typename ObjectInheritedType>
    Event(EventType type, ObjectInheritedType* target) {
        m_type = type;
        m_target = reinterpret_cast<Object*>(target);
    }

    EventType type() {
        return m_type;
    }

    Object* target() {
        return m_target;
    }

};

#endif // _H_EVENT_H_