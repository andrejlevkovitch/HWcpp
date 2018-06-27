//quick_sort.cpp

#include"sort.hpp"

int *quick_sort(int *array, const size_t size)
{
    q_sort(array, 0, size - 1);
    return array;
}

void q_sort(int *array, int first, int last)
{
    srand (time (NULL));

    auto left {first};
    auto right {last};
    auto midle {array[left + rand () % (right - left + 1)]};

    while (left <= right) {
        while (array[left] < midle) {
            ++left;
        }
        while (array[right] > midle) {
            --right;
        }

        if (left <= right) {
            std::swap(array[left], array[right]);
            ++left;
            --right;
        }
    }

    if (first < right) {
        q_sort (array, first, right);
    }

    if (last > left) {
        q_sort (array, left, last);
    }

    return;
}
