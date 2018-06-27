//buble_sort.cpp

#include"sort.hpp"

int *buble_sort(int *array, const size_t size)
{
    for (int i {}; i < size - 1; ++i) {
        for (int j {}; j < size - 1 - i; ++j) {
           if (array[j] > array[j + 1]) {
               std::swap(array[j], array[j + 1]);
           }
        }
    }

    return array;
}
