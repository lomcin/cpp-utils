#ifndef _H_DYNAMIC_TYPER_H_
#define _H_DYNAMIC_TYPER_H_
#include "BasicTypes.hpp"

#define registerClass() {className(__FUNCTION__); DynamicType::insert(className());}

namespace DynamicType {
    static stringsSet m_classes;

    static void insert(std::string class_name) {
        DynamicType::m_classes.insert(class_name);
    };

    static strings classes() {
        return strings(DynamicType::m_classes.begin(),DynamicType::m_classes.end());
    };
};

class DynamicTyper {

    std::string m_class_name;

    public:
    DynamicTyper() {
        registerClass()
    }

    std::string className() {
        return m_class_name;
    }

    void className(std::string class_name) {
        m_class_name = class_name;
    }

};

#endif // _H_DYNAMIC_TYPER_H_