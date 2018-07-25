// library.hpp

#pragma once

#include "book.hpp"
#include "reader.hpp"

#include <list>
#include <map>
#include <tuple>
#include <utility>

typedef std::multimap<Book, size_t> Bookcase;
typedef std::map<Reader, std::list<Book>> Journal;

class Library {
public:
  static unsigned short MAX_COUNT_IN_ONE_HAND();

private:
  Bookcase bookcase_;
  Journal journal_;
  std::string file_bookcase_;
  std::string file_journal_;

public:
  Library(const std::string &fileBook, const std::string &fileJournal);
  void add_book(const Book &);
  void add_book(const std::string &name, const std::string &autor);
  bool remove_book(const Book &);
  bool remove_book(const std::string &name, const std::string &autor);
  std::tuple<Bookcase::iterator, Bookcase::iterator, bool>
  find_book(const Book &);
  std::tuple<Bookcase::iterator, Bookcase::iterator, bool>
  find_book(const std::string &name, const std::string &autor = "");
  std::list<Bookcase::iterator> find_autor(const std::string &autor);
  void show_all_books() const;

  void register_reader(const Reader &); // generated invalid_argument
  void
  register_reader(const std::string &name,
                  const std::string &surname); // generated invalid_argument
  void erase_reader(const Reader &);
  void erase_reader(const std::string &name, const std::string &surname);
  std::pair<Journal::iterator, bool> find_reader(const Reader &);
  std::pair<Journal::iterator, bool> find_reader(const std::string &name,
                                                 const std::string &surname);
  void show_all_readers() const;
  void show_readers_books(const Reader &) const; // generated invalid_argument
  void show_readers_books(
      const std::string &name,
      const std::string &surname) const; // generated invalid_argument

  void
  give_book_reader(const Book &,
                   const Reader &); // generated invalid_argument & lenght_error
  void take_book_reader(const Book &,
                        const Reader &); // generated invalid_argument
};
