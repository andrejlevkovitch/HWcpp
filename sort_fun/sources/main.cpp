//main.cpp

#include<iostream>
#include<cstring>
#include<limits>

#include"sort.hpp"

int main(int argc, char *argv[])
{
    if (argc > 1 && !strcmp(argv[1], HELP)) {
        std::cout << "Use flags:\n" <<
                     AUTO << " - for auto filling in array\n" <<
                     MANUALLY << " - for manually input in array\n" <<
                     std::endl;
        std::cout << "Sort metods:\n";
        for (int i {}; i < SORT_OPTIONS.size(); ++i) {
            std::cout << SORT_OPTIONS[i] << std::endl;
        }
        return 0;
    }

    size_t size {};
    do {
        std::cout << "Input size of array (0 < n <= " << MAX_SIZE << "): ";
        while (!(std::cin >> size)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Wrong input! Try again.\n";
        }
    } while (size > MAX_SIZE);

    auto *array = new int[size];

    if (argc > 1 && !strcmp(argv[1], MANUALLY)) {
        std::cout << "Input values" << std::endl;
        for (int i {}; i < size; ++i) {
            if (!(std::cin >> array[i])) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Be careful!\n" << "You need start again.\n";
                delete [] array;
                return 1;
            }
        }
    }
    else {
        feeling_in(array, size);
    }

    output_arr(array, size);

    unsigned short option {};
    if (argc > 2) {
        for (int i {}; i < SORT_OPTIONS.size(); ++i) {
            if (SORT_OPTIONS[i] == argv[2]) {
                option = i;
            }
        }
    }

    std::cout << "Use " << SORT_OPTIONS[option] << std::endl;
    switch (option) {
        case 1:
            swap_sort(array, size);
            break;
        case 2:
            insert_sort(array, size);
            break;
        case 3:
            merge_sort(array, size);
            break;
        case 4:
            quick_sort(array, size);
            break;
        case 0:
        default:
            buble_sort(array, size);
            break;
    };

    output_arr(array, size);

    delete [] array;

    return 0;
}
