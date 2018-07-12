//main.cpp

#include<iostream>
#include<algorithm>

#include"stack.hpp"

int main(int argc, char *argv[])
{
    Stack<int> alfa;

    if (alfa.begin() != alfa.end()) {
        std::cout << "not_empty\n";
    }
    else {
        std::cout << "empty\n";
    }

    for (int i {}; i < 10; ++i) {
        alfa.push(i);
    }

    std::cout << alfa.size() << std::endl << std::endl;

    int a = 20;
    alfa.push(a);


    for (const auto & temp : alfa) {
        std::cout << temp << " ";
    }
    std::cout << std::endl;

    std::for_each(alfa.begin(), alfa.end(), [&](auto & in){in = 1;});

    std::cout << "iterators in\n";
    for (auto i = alfa.begin(); i != alfa.end(); ++i) {
        std::cout << *i << " ";
    }
    std::cout << std::endl;
    std::cout << "iterators out\n";


    return 0;
}
