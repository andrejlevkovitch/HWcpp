//main.cpp

#include<iostream>
#include<fstream>
#include"avl_tree.hpp"

int main(int argc, char *argv[])
{
    std::ofstream fout;
    std::ifstream fin;

    struct Comp {
        bool operator()(int a, int b) const {return a > b;};
    };

    AVL_tree<int, Comp> alfa;

    int size {};
    int temp {};
    fin.open("../data/input.txt");
    std::cout << "read from file start\n";
    if (fin.is_open()) {
        fin >> size;
        for (int i {}; i < size; ++i) {
            fin >> temp;
            alfa.insert(temp);
        }
        fin.close();
    }
    std::cout << "read from file end\n";

    std::cout << std::endl;

    std::cout << "write in file start\n";
    fout.open("../data/output.txt");
    if (fout.is_open()) {
        fout << alfa.size() << std::endl;
        fout << alfa;
        fout.close();
    }
    std::cout << "write in file end\n";

    std::cout << std::endl;

    std::cout << "proverka\n";
    fin.open("../data/output.txt");
    if (fin.is_open()) {
        fin >> size;
        int previous {};
        for (int i {}; i < size; ++i) {
            fin >> temp;
            if (i > 0 && alfa.key_comp()(temp, previous)) {
                std::cout << "WRONG!!!\n";
                break;
            }
            previous = temp;
        }
        fin.close();
    }
    std::cout << "proverka finished\n";

    return 0;
}
