/*
MIT License

Copyright (c) 2020-2024 Lucas Maggi

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include <bits/stdc++.h>
#include "Node.hpp"

using namespace std;

void values_samples()
{
    // Print some info about the sample
    cout << __FUNCTION__ << endl;
    int width = 128, height = 128;

    printf("W x H: %d %d\n", width, height);
    printf("NodeScope size: %d\n", static_cast<int>(NodeScope::nodes.size()));

    {
        // These Nodes only exists in this scope.
        Node nwidth(&width, 640);
        Node nheight(&height, 480);

        printf("W x H: %d %d\n", width, height);

        Node nheight2(nheight); // First redundant reference for the same variable node
        nheight2 = 240;
        nheight2 = nheight.set(480);

        printf("W x H: %d %d\n", width, height);

        Node *nheight3 = new Node(&height); // Second redundant reference for the same variable node
        nheight3->set(120);

        printf("W x H: %d %d\n", width, height);
        printf("nodes W x H: %d %d\n", nwidth.get<int>(), nheight.get<int>());
        width = 32;
        height = 32;
        printf("nodes W x H: %d %d\n", nwidth.get<int>(), nheight.get<int>());

        nwidth.set(16);
        nheight2.set(16);
        printf("W x H: %d %d\n", width, height);
        printf("nodes W x H: %d %d\n", nwidth.get<int>(), nheight3->get<int>());
        printf("NodeScope size: %d\n", static_cast<int>(NodeScope::nodes.size()));
        delete nheight3;
    }

    printf("NodeScope size: %d\n", static_cast<int>(NodeScope::nodes.size()));
}

int main()
{

    values_samples();

    return 0;
}
