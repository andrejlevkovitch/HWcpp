// library.hpp

#pragma once

#include "book.hpp"
#include "reader.hpp"

#include <list>
#include <map>
#include <tuple>
#include <utility>

typedef std::multimap<Book, unsigned short> Bookcase;
typedef std::map<Reader, std::list<Book>> Journal;

class Library {
public:
  static unsigned short MAX_COUNT_IN_ONE_HAND();

public:
  Bookcase bookcase_;
  Journal journal_;
  std::string file_bookcase_;
  std::string file_journal_;

public:
  Library(const std::string &fileBook, const std::string &fileJournal);
  ~Library();
  void add_book(const Book &, unsigned short count = 1);
  void add_book(const std::string &name, const std::string &autor,
                unsigned short count = 1);
  bool remove_book(const Book &);
  bool remove_book(const std::string &name, const std::string &autor);
  std::tuple<Bookcase::iterator, Bookcase::iterator, bool>
  find_book(const Book &);
  std::tuple<Bookcase::iterator, Bookcase::iterator, bool>
  find_book(const std::string &name, const std::string &autor = "");
  std::list<Bookcase::iterator> find_autor(const std::string &autor);

  std::pair<Journal::iterator, bool> register_reader(const Reader &);
  std::pair<Journal::iterator, bool>
  register_reader(const std::string &name, const std::string &surname);
  bool erase_reader(const Reader &);
  bool erase_reader(const std::string &name, const std::string &surname);
  std::pair<Journal::iterator, bool> find_reader(const Reader &);
  std::pair<Journal::iterator, bool> find_reader(const std::string &name,
                                                 const std::string &surname);

  void
  give_book_reader(const Book &,
                   const Reader &); // generated invalid_argument & lenght_error
  void take_book_reader(const Book &,
                        const Reader &); // generated invalid_argument

  size_t getBooksNum() const;
  size_t getReadersNum() const;
  std::pair<Bookcase::iterator, Bookcase::iterator> first_last_book();
  std::pair<Journal::iterator, Journal::iterator> first_last_reader();
};
