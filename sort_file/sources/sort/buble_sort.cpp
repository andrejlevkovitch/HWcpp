//buble_sort.cpp

#include"file_sort.hpp"
#include<climits>
#include<iostream>
#include<stdexcept>

short buble_sort(std::fstream &ios, std::string &file)
{
    if (ios.is_open()) {
        ios.close();
    }
    ios.open(file);
    if (ios.is_open()) {
        unsigned short size {};
        for (int i {}; ios >> i; ++size) {
        }
        ios.clear();
        ios.seekg(0, std::ios_base::beg);
        for (int i {}; i < size - 1; ++i) {
            int first {INT_MIN};
            int second {};
            ios.seekg(0, std::ios_base::beg);
            for (int j {}; j < size - i; ++j) {
                ios >> second;
                if (first > second) {
                    ios.seekp(-9, std::ios_base::cur);
                    ios << second << ' ' << first;
                }
                else {
                    first = second;
                }
            }
        }
        ios.close();
        return size;
    }
    else {
        throw std::domain_error("Program can't open the file!\n");
    }
}
