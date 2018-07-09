//count_sort.cpp

#include"file_sort.hpp"
#include<vector>

const int MIN_VALUE {1000};

short count_sort(std::fstream &ios, std::string &file) {
    if (ios.is_open()) {
        ios.close();
    }
    ios.open(file);
    if (ios.is_open()) {
        unsigned short size {};
        std::vector<short> count_arr(9000, 0);
        short value {};
        while (ios >> value) {
            count_arr[value - MIN_VALUE]++;
            size++;
        }
        ios.clear();
        ios.seekg(0, std::ios_base::beg);
        for (int i {}; i < count_arr.size(); ++i) {
            while (count_arr[i]--) {
                ios << i + MIN_VALUE << ' ';
            }
        }
        ios.close();
        return size;
    }
    else {
        throw std::domain_error("Program can't open the file!\n");
    }
}
