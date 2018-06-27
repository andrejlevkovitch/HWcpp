//merge_sort.cpp

#include"sort.hpp"

int *merge_sort(int *array, const size_t size)
{
    merge(array, 0, size - 1);
    return array;
}

void merge(int *array, int first, int last)
{
    int midle {};

    if (first < last) {
        midle = first + (last - first) / 2;

        merge(array, first, midle);
        merge(array, midle + 1, last);

        msort(array, first, midle, last);
    }

    return;
}

void msort(int *array, int first, int midle, int last)
{
    int iterator_lhs {}, iterator_rhs {};

    auto iterator {first};

    auto n1 {midle - first + 1};
    auto n2 {last - midle};

    auto array_lhs = new std::remove_reference_t<decltype(*array)>[n1];
    auto array_rhs = new std::remove_reference_t<decltype(*array)>[n2];

    for (int i {}; i < n1; ++i) {
        array_lhs[i] = array[first + i];
    }
    for (int i {}; i < n2; ++i) {
        array_rhs[i] = array[midle + 1 + i];
    }

    while (iterator_lhs < n1 && iterator_rhs < n2) {
        if (array_lhs[iterator_lhs] > array_rhs[iterator_rhs]) {
            array[iterator] = array_rhs[iterator_rhs];
            ++iterator_rhs;
        }
        else {
            array[iterator] = array_lhs[iterator_lhs];
            ++iterator_lhs;
        }

        ++iterator;
    }

    if (iterator_lhs == n1) {
        for (int i {}; i < n2 - iterator_rhs; ++i) {
            array[iterator + i] = array_rhs[i + iterator_rhs];
        }
    }
    else {
        for (int i {}; i < n1 - iterator_lhs; ++i) {
            array[iterator + i] = array_lhs[i + iterator_lhs];
        }
    }

    delete [] array_lhs;
    delete [] array_rhs;

    return;
}
