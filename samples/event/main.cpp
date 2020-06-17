#include <bits/stdc++.h>
#include "Object.hpp"

using namespace std;

int Changed(Event e) {
    printf("Changed something!\n");
}

int Updated(Event e) {
    printf("Updated something!\n");
}

/*  This sample show how to use simple functions to listen to events.
*   And how a event can be dispatched.
*/
void sample0() {
    // Print some info about the sample
    cout << __FUNCTION__ << endl;

    EventManager a;
    
    Event e(EventType::onChange, &a);

    a.addEventListener(EventType::onChange, Changed);
    a.addEventListener(EventType::onUpdate, Updated);

    a.dispatchEvent(e);
    a.dispatchEvent(EventType::onUpdate);

}

class AClass : public Object {
    public:
    AClass(std::string name):Object(name)
    {
        registerClass()
    }
    int onchange(Event e) {
        std::cout << "Name: " << name() << std::endl;
        name() += "_" + name(); // If the name() was "a", then it will be "a_a"
        std::cout << "Modified Name: " << name() << std::endl;
        std::cout << "Target name " << e.target()->name() << std::endl;
    }
};


// This samples shows how to use instance's methods as listeners
void objectMethodContext() {
    // Print some info about the sample
    cout << __FUNCTION__ << endl;

    Object obj("obj");

    // Creating two instances of AClass
    AClass a("a"), b("b");
    
    // Adding toFunction solves the problem with calling methods from objects
    obj.addEventListener(EventType::onFrame,toFunction(a.onchange));
    obj.addEventListener(EventType::onFrame,toFunction(b.onchange));

    obj.dispatchEvent(EventType::onFrame);
    obj.dispatchEvent(EventType::onFrame);
    obj.dispatchEvent(EventType::onFrame);

    // As you can see here, the expected behavior is to print a_a and b_b
    std::cout << "Modified Name for a: " << a.name() << endl;
    std::cout << "Modified Name for b: " << b.name() << endl;
    
}


void dynamicType() {
    strings classes = DynamicType::classes();
    cout << endl << "Classes: " << endl;
    for (string &c : classes) {
        cout << c << endl;
    }
    cout << endl;
    Object obj("obj");
    cout << obj.name() << " is a " << obj.className() << endl;
}

int main () {

    sample0();
    objectMethodContext();
    dynamicType();

    return 0;
}
