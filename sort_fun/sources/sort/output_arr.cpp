//output_arr.cpp

#include<iostream>
#include"sort.hpp"

void output_arr(const int *array, const size_t size)
{
    for (int i {}; i < size; ++i) {
        std::cout << array[i] << " ";
    }
    std::cout << std::endl;
    return;
}

