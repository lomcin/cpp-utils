#ifndef _H_OBJECT_H_
#define _H_OBJECT_H_
#include "EventManager.hpp"

class Object : public EventManager{
    std::string m_name;
    public:
    Object(std::string name):m_name(name)
    {};
    std::string name() {
        return m_name;
    }
};

#endif // _H_OBJECT_H_