#ifndef _H_OBJECT_H_
#define _H_OBJECT_H_
#include "EventManager.hpp"
#include "DynamicTyper.hpp"

class Object : public EventManager, public DynamicTyper {
    std::string m_name;
    public:
    Object(std::string name):m_name(name)
    {
        registerClass()
    };
    std::string& name() {
        return m_name;
    }
};

#endif // _H_OBJECT_H_