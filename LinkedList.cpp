#include "LinkedList.h"

#include <iostream>

int main()
{
    std::cout << "Hello World!\n";

    // Expected usage
    LinkedList<int> original = { 1, 42, 3 };
    auto tail = original.split_when(
        [](const int& value)) {
        return value == 42;
    }
        );
        // original now is { 1 }
        // tail now is { 42, 3 }
}

