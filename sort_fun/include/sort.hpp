//sort.hpp

#pragma once

#ifndef __cplusplus
#error C++ is required
#elif __cplusplus <= 201103L
#error C++14 is required
#endif

#include<cstddef>
#include<string>
#include<vector>

const char HELP[] {"-help"};
const char AUTO[] {"-auto"};
const char MANUALLY[] {"-manually"};
const std::vector<std::string> SORT_OPTIONS {"-buble", "-swap", "-insert",
    "-merge", "-quick"};

const int MAX_SIZE = 100;
const int MIN_VALUE = -MAX_SIZE;
const int MAX_VALUE = MAX_SIZE;

int *feeling_in(int *array, const size_t size);

void output_arr(const int *array, const size_t size);

int *buble_sort(int *array, const size_t size);
int *swap_sort(int *array, const size_t size);
int *insert_sort(int *array, const size_t size);
int *merge_sort(int *array, const size_t size);
    void merge(int *array, int first, int last);
    void msort(int *array, int first, int midle, int last);
int *quick_sort(int *array, const size_t size);
    void q_sort(int *array, int first, int last);
