#include "LinkedList.h"

#include <iostream>
#include <string>
#include <string_view>

int main()
{
    // Expected usage
    LinkedList<int> original = { 1, 42, 3 };

    original.push_front(2);
    original.push_front(69);
    original.pop_front();

    std::cout << "Orignial: ";

    for (int o : original) {
        std::cout << o << " ";
    }

    std::cout << "\nSize: " << original.size() << '\n';

    auto tail = original.split_when(
        [](const int& value) {
            return value == 42;
        }
    );

    std::cout << "Original: ";
    
    for (auto o : original) {
        std::cout << o << " ";
    }

    std::cout << "\nTail: ";

    for (auto t : tail) {
        std::cout << t << " ";
    }

    LinkedList<std::string> stringList = { "hi", "bye", "bnjour", "siema" };

    std::cout << "\nString List: ";

    for (std::string_view s : stringList) {
        std::cout << s << " ";
    }
}

