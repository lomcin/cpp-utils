#include <bits/stdc++.h>
#include "Object.hpp"

using namespace std;

void Changed(Event e) {
    printf("Changed something!\n");
}

void Updated(Event e) {
    printf("Updated something!\n");
}

/*  This sample show how to use simple functions to listen to events.
*   And how a event can be dispatched.
*/
void sample0() {
    // Print some info about the sample
    cout << __FUNCTION__ << endl;

    Object a;
    
    Event e(EventType::onChange, &a);

    a.addEventListener(EventType::onChange, Changed);
    a.addEventListener(EventType::onUpdate, Updated);

    a.dispatchEvent(e);
    a.dispatchEvent(EventType::onUpdate);

}

class AClass {
    std::string m_name;
    public:
    AClass(std::string name) {
        m_name.assign(name.begin(), name.end());
    }
    void onchange(Event e) {
        std::cout << "Name: " << m_name << endl;
        m_name += "_" + m_name; // If the m_name was "a", then it will be "a_a"
        std::cout << "Modified Name: " << m_name << endl;
    }
    std::string name() {
        return m_name;
    }
};


// This samples shows how to use instance's methods as listeners
void objectMethodContext() {
    // Print some info about the sample
    cout << __FUNCTION__ << endl;

    Object obj;

    // Creating two instances of AClass
    AClass a("a"), b("b");
    
    // Adding toFunction solves the problem with calling methods from objects
    obj.addEventListener(EventType::onFrame,toFunction(a.onchange));
    obj.addEventListener(EventType::onFrame,toFunction(b.onchange));

    obj.dispatchEvent(EventType::onFrame);

    // As you can see here, the expected behavior is to print a_a and b_b
    std::cout << "Modified Name for a: " << a.name() << endl;
    std::cout << "Modified Name for b: " << b.name() << endl;
}

int main () {

    sample0();
    objectMethodContext();

    return 0;
}
