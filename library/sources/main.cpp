//main.cpp

#include<iostream>
#include"library.hpp"

#include<limits>

int main(int argc, char *argv[])
{
    Library my_library;
    std::cout << "LIBRARY\n";
    std::cout << "Interface:\n";
    std::cout <<
        "1 - find book;\n" <<
        "2 - find reader;\n" <<
        "3 - add book;\n" <<
        "4 - add reader;\n" <<
        "5 - show books;\n" <<
        "6 - show readers;\n" <<
        "7 - show reader's books;\n" <<
        "8 - give the reader a book;\n" <<
        "9 - return book from reader;\n" <<
        "10- erase book;\n" <<
        "11- erase reader.\n";

    std::cout << std::endl;

    int operace {};
    std::cout << "What you want to do?\n";
    while (std::cin >> operace) {
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        switch (operace) {
            case 1:
                {
                    std::cout << "Input name book:\n";
                    std::string name;
                    std::getline(std::cin, name);
                    std::cout << "Input autor:\n";
                    std::string autor;
                    std::getline(std::cin, autor);
                    Book book {name, autor};
                    auto finded_book = my_library.find_book(book);
                    if (finded_book.second) {
                        std::cout << "We have this book\n";
                    }
                    else {
                        std::cout << "We haven't this book now\n";
                    }
                }
                break;
            case 2:
                {
                    std::cout << "Input name:\n";
                    std::string name;
                    std::getline(std::cin, name);
                    std::cout << "Input surname:\n";
                    std::string surname;
                    std::getline(std::cin, surname);
                    Reader reader {name, surname};
                    auto finded_reader = my_library.find_reader(reader);
                    if (finded_reader.second) {
                        std::cout << "We have this reader\n";
                    }
                    else {
                        std::cout << "We haven't this reader now\n";
                    }
                }
                break;
            case 3:
                {
                    std::cout << "Input name book:\n";
                    std::string name;
                    std::getline(std::cin, name);
                    std::cout << "Input autor:\n";
                    std::string autor;
                    std::getline(std::cin, autor);
                    Book book {name, autor};
                    my_library.add_book(book);
                }
                break;
            case 4:
                {
                    std::cout << "Input name:\n";
                    std::string name;
                    std::getline(std::cin, name);
                    std::cout << "Input surname:\n";
                    std::string surname;
                    std::getline(std::cin, surname);
                    Reader reader {name, surname};
                    my_library.register_reader(reader);
                }
                break;
            case 5:
                {
                    my_library.show_all_books();
                }
                break;
            case 6:
                {
                    my_library.show_all_readers();
                }
                break;
            case 7:
                {
                    std::cout << "Input name:\n";
                    std::string name;
                    std::getline(std::cin, name);
                    std::cout << "Input surname:\n";
                    std::string surname;
                    std::getline(std::cin, surname);
                    Reader reader {name, surname};
                    my_library.show_readers_books(reader);
                }
                break;
            case 8:
                {
                    std::cout << "Input name book:\n";
                    std::string name;
                    std::getline(std::cin, name);
                    std::cout << "Input autor:\n";
                    std::string autor;
                    std::getline(std::cin, autor);
                    Book book {name, autor};

                    std::cout << "Input name:\n";
                    std::getline(std::cin, name);
                    std::cout << "Input surname:\n";
                    std::string surname;
                    std::getline(std::cin, surname);
                    Reader reader {name, surname};

                    my_library.took_book(reader, book);
                }
                break;
            case 9:
                {
                    std::cout << "Input name book:\n";
                    std::string name;
                    std::getline(std::cin, name);
                    std::cout << "Input autor:\n";
                    std::string autor;
                    std::getline(std::cin, autor);
                    Book book {name, autor};

                    std::cout << "Input name:\n";
                    std::getline(std::cin, name);
                    std::cout << "Input surname:\n";
                    std::string surname;
                    std::getline(std::cin, surname);
                    Reader reader {name, surname};

                    my_library.return_book(reader, book);
                }
                break;
            case 10:
                {
                    std::cout << "Input name book:\n";
                    std::string name;
                    std::getline(std::cin, name);
                    std::cout << "Input autor:\n";
                    std::string autor;
                    std::getline(std::cin, autor);
                    Book book {name, autor};
                    my_library.erase_book(book);
                }
                break;
            case 11:
                {
                    std::cout << "Input name:\n";
                    std::string name;
                    std::getline(std::cin, name);
                    std::cout << "Input surname:\n";
                    std::string surname;
                    std::getline(std::cin, surname);
                    Reader reader {name, surname};
                    my_library.erase_reader(reader);
                }
                break;
            default:
                break;
        }
        std::cout << "What you want to do?\n";
    }

    return 0;
}
