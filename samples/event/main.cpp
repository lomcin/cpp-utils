#include <bits/stdc++.h>
#include "Object.hpp"

using namespace std;

void sample0() {
    Object a;
    Event e(EventType::onChange, &a);
    cout << "Sample 0" << endl;
    cout << e.type() << endl;
}

int main () {

    sample0();

    return 0;
}
