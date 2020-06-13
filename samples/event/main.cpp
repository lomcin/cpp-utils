#include <bits/stdc++.h>
#include "Object.hpp"

using namespace std;

void func(Event e) {
    printf("changed something!\n");
}

void sample0() {
    Object a;
    Event e(EventType::onChange, &a);
    a.addEventListener(EventType::onChange,func);
    a.dispatchEvent(e);
    cout << "Sample 0" << endl;
    cout << e.type() << endl;
}

int main () {

    sample0();

    return 0;
}
