//swap_sort.cpp

#include"sort.hpp"

int *swap_sort(int *array, const size_t size)
{
    int temp {};
    int index {};

    for (int i {}; i < size; ++i) {
        temp = array[i];
        index = i;

        if (i != 0 && array[i - 1] == temp) {
        }
        else {
            for (int j {i + 1}; j < size; ++j) {
                if (temp > array[j]) {
                    temp = array[j];
                    index = j;
                }
            }
        }

        if (index != i) {
            array[index] = array[i];
            array[i] = temp;
        }
    }

    return array;
}
