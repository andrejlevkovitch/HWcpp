//file_sort.hpp

#pragma once

#include<cstddef>
#include<string>
#include<fstream>
#include<cstdbool>

const std::string WAY_TO_FILE {"../data/"};
const std::string NAME_FILE {"data.txt"};

short buble_sort(std::fstream &, std::string &file);//generat exception
short count_sort(std::fstream &, std::string &file);//generat exception
