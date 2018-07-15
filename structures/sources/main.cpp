//main.cpp

#include<iostream>
#include<fstream>
#include<algorithm>

#include"avl.hpp"

int main(int argc, char *argv[])
{
    if (argc > 2) {
        std::ofstream fout;
        std::ifstream fin;

        struct Comp {
            bool operator()(int a, int b) const {return a > b;};
        };

        AVL_tree<int, Comp> alfa;

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

        std::cout << "Element 29995 met " <<
            alfa.count(29995) << " times" << std::endl;

        auto finded = std::find(alfa.begin(), alfa.end(), 29970);
        if (finded != alfa.end()) {
            std::cout << *finded << std::endl;
        }
        else {
            std::cout << "no find" << std::endl;
        }
        finded = alfa.find(28851);
        if (finded != alfa.end()) {
            std::cout << *finded << std::endl;
        }
        else {
            std::cout << "no find" << std::endl;
        }


        std::cout << "write in file start\n";
        fout.open(argv[2]);
        if (fout.is_open()) {
            fout << alfa.size() << '\n';
//          std::for_each(
//                  alfa.rbegin(), alfa.rend(),
//                  [&](auto & element){fout << element << ' ';});
            for (auto & i : alfa) {
                fout << i << ' ';
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
