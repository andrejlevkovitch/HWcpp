//library.hpp

#pragma once

#include"avl.hpp"
#include"book.hpp"
#include"reader.hpp"

#include<map>
#include<list>
#include<tuple>

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
        std::pair<Bookcase::IteratorBi, bool> find_book(const Book &) const;
        void show_all_books() const;

        void register_reader(const Reader &);
        void erase_reader(const Reader &);
        std::pair<Journal::const_iterator, bool> find_reader(const Reader &) const;
        void show_all_readers() const;
        void show_readers_books(const Reader &) const;

        void took_book(const Reader &, const Book &);
        void return_book(const Reader &, const Book &);
};
