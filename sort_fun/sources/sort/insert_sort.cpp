//insert_sort.cpp

#include"sort.hpp"

int *insert_sort(int *array, const size_t size)
{
    int temp {};
    for (int i {1}; i < size; ++i) {
        temp = array[i];
        for (int j {i - 1}; j >= 0; --j) {
            if (array[j] > temp) {
                std::swap(array[j], array[j + 1]);
            }
            else {
                array[j + 1] = temp;
                break;
            }

            if (j == 0) {
                array[j] = temp;
            }
        }
    }

    return array;
}
