#include <iostream>
#include "CStringList.h"
#include <algorithm>

int main()
{
    CStringList list;
    list.PushBack("a");
    list.PushBack("b");
    list.PushBack("c");
    list.PushBack("d");
    list.PushBack("e");
    list.PushBack("f");
    std::reverse(list.begin(), list.end());
    for (auto it = list.rbegin(); it != list.rend(); ++it) {
        std::cout << *it;
    }
    std::cout << std::endl;
    for (auto item: list)
    {
        std::cout << item;
    }
}


