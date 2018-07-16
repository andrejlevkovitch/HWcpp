//library.hpp

#pragma once

#include"avl.hpp"
#include"book.hpp"
#include"reader.hpp"

#include<map>
#include<list>

typedef AVL_tree<Book> Bookcase;
typedef std::map<Reader, std::list<Book>> Journal;

class Library {
    private:
        Bookcase bookcase_;
        Journal journal_;
    public:
        Library ();
        void add_book(const Book &);
        void erase_book(const Book &);
        void find_book(const Book &);
        void show_all_books();
        void register_reader(const Reader &);
        void erase_reader(const Reader &);
        void find_reader(const Reader &);
        void show_all_readers();
        void took_book(const Reader &, const Book &);
        void return_book(const Reader &, const Book &);
};
