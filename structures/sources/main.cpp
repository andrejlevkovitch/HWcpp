//main.cpp

#include<iostream>
#include<fstream>
#include"avl_tree.hpp"

int main(int argc, char *argv[])
{
    if (argc > 2) {
        std::ofstream fout;
        std::ifstream fin;

        struct Comp {
            bool operator()(int a, int b) const {return a > b;};
        };

        AVL_tree<int> alfa;

        int size {};
        int temp {};
        fin.open(argv[1]);
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
        fout.open(argv[2]);
        if (fout.is_open()) {
            fout << alfa.size() << '\n';
            for (auto & temp : alfa) {
                fout << temp << ' ';
            }
            fout.close();
        }
        std::cout << "write in file end\n";

        std::cout << std::endl;

        std::cout << "proverka\n";
        fin.open(argv[2]);
        if (fin.is_open()) {
            fin >> size;
            int previous {};
            auto comp {alfa.key_comp()};
            for (int i {}; i < size; ++i) {
                fin >> temp;
                if (i > 0 && comp(temp, previous)) {
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
    else {
        return 1;
    }

}
