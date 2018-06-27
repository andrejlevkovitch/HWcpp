//feeling_in.cpp

#include<cstddef>
#include"sort.hpp"
#include<cstdlib>
#include<ctime>

int *feeling_in(int *array, const size_t size)
{
    srand(time(NULL));
    for (int i {}; i < size; ++i) {
        array[i] = MIN_VALUE + rand() % (MAX_VALUE * 2 + 1);
    }
    return array;
}
