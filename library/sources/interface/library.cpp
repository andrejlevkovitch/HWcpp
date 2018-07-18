//library.cpp

#include<iostream>
#include"library.hpp"

#include<algorithm>
#include<exception>

Library::Library ()
{
}

void Library::add_book(const Book & book)
{
    bookcase_.insert(book);
    return;
}

void Library::erase_book(const Book & book)
{
    bookcase_.erase(book);
    return;
}

std::pair<Bookcase::IteratorBi, bool> Library::find_book(const Book & book) const
{
    auto finded = bookcase_.find(book);
    bool attribute = finded != bookcase_.end();
    return std::make_pair(finded, attribute);
}

void Library::show_all_books() const
{
    for (auto & i : bookcase_) {
        std::cout << i << std::endl;
    }
}

void Library::register_reader(const Reader & reader)
{
    journal_[reader];
    return;
}

void Library::erase_reader(const Reader & reader)
{
    journal_.erase(reader);
    return;
}

std::pair<Journal::const_iterator, bool>
Library::find_reader(const Reader & reader) const
{
    auto finded = journal_.find(reader);
    bool attribute = finded != journal_.end();
    return std::make_pair(finded, attribute);
}

void Library::show_all_readers() const
{
    for (auto & i : journal_) {
        std::cout << i.first << std::endl;
    }
    return;
}

void Library::show_readers_books(const Reader & reader) const
{
    try {
        auto books = journal_.at(reader);
        for (auto & i : books) {
            std::cout << i << std::endl;
        }
    }
    catch (std::out_of_range & except) {
        std::cout << "We haven't this reader\n";
    }
    return;
}

void Library::took_book(const Reader & reader, const Book & book)
{
    if (!find_book(book).second) {
        std::cout << "We haven't this book\n";
    }
    else {
        try {
            journal_.at(reader).push_back(book);
            bookcase_.erase(book);
        }
        catch (std::out_of_range & except) {
            std::cout << "We haven't this reader\n";
        }
    }
    return;
}

void Library::return_book(const Reader & reader, const Book & book)
{
    try {
        auto finded = journal_.at(reader);
        if (std::find(finded.begin(), finded.end(), book) == finded.end()) {
            std::cout << "Reader don't have this book\n";
        }
        else {
                finded.remove(book);
                bookcase_.insert(book);
        }
    }
    catch (std::out_of_range & except) {
        std::cout << "We haven't this reader\n";
    }
    return;
}
