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

        Node nheight2(nheight); // First edundant reference for the same variable node
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
