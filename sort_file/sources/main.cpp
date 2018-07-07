//main.cpp

#include<iostream>

#include"file_sort.hpp"

int main(int argc, char *argv[])
{
    std::fstream ios;
    std::string file;
    if (argc > 1) {
        file = argv[1];
    }
    else {
        file = WAY_TO_FILE + NAME_FILE;
    }
    try {
        std::cout << "Started sortring of: " << file << " file\n";
        int digit = buble_sort(ios, file);
        std::cout << "Finished sorting of: " << file << " file\n";
        std::cout << "In file was " << digit << " numbers\n";
    }
    catch (std::domain_error error) {
        std::cout << error.what();
    }
    return 0;
}
