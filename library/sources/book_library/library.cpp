// library.cpp

#include "library.hpp"

#include <algorithm>
#include <exception>
#include <fstream>

Library::Library(const std::string &fileBook, const std::string &fileJournal)
    : file_bookcase_{fileBook}, file_journal_{fileJournal} {
  std::fstream fin;
  fin.open(file_bookcase_);
  if (fin.is_open()) {
    std::string name;
    std::string autor;
    while (1) {
      std::getline(fin, name);
      std::getline(fin, autor);
      if (fin.eof()) {
        break;
      } else {
        add_book(name, autor);
      }
    }
    fin.close();
  }
  fin.open(file_journal_);
  if (fin.is_open()) {
    std::string name;
    std::string surname;
    while (1) {
      std::getline(fin, name);
      std::getline(fin, surname);
      if (fin.eof()) {
        break;
      } else {
        register_reader(name, surname);
      }
    }
    fin.close();
  }
}

unsigned short Library::MAX_COUNT_IN_ONE_HAND() {
  static unsigned short retval{5};
  return retval;
}

void Library::add_book(const Book &book) {
  auto finded = find_book(book);
  if (std::get<2>(finded)) {
    std::get<0>(finded)->second++;
  } else {
    bookcase_.insert(std::make_pair(book, 1));
  }
  return;
}

void Library::add_book(const std::string &name, const std::string &autor) {
  add_book(Book{name, autor});
  return;
}

bool Library::remove_book(const Book &book) {
  auto finded = find_book(book);
  if (std::get<2>(finded)) {
    if (!--(std::get<0>(finded)->second)) {
      bookcase_.erase(std::get<0>(finded));
    }
    return true;
  } else {
    return false;
  }
}

bool Library::remove_book(const std::string &name, const std::string &autor) {
  return remove_book(Book{name, autor});
}

std::tuple<Bookcase::iterator, Bookcase::iterator, bool>
Library::find_book(const Book &book) {
  auto finded = bookcase_.equal_range(book);
  bool exact_math{false};
  if (finded.first == finded.second) {
  } else {
    if (!book.get_autor().empty()) {
      for (auto i = finded.first; i != finded.second; ++i) {
        if (i->first.get_autor() == book.get_autor()) {
          finded.first = i;
          finded.second = std::next(i);
          exact_math = true;
          break;
        }
      }
      if (!exact_math) {
        finded.first = finded.second;
      }
    } else if (std::distance(finded.first, finded.second) == 1) {
      exact_math = true;
    }
  }
  return std::make_tuple(finded.first, finded.second, exact_math);
}

std::tuple<Bookcase::iterator, Bookcase::iterator, bool>
Library::find_book(const std::string &name, const std::string &autor) {
  return find_book(Book{name, autor});
}

std::list<Bookcase::iterator> Library::find_autor(const std::string &autor) {
  std::list<Bookcase::iterator> retval;
  struct Comp {
    std::string autor_;
    Comp(const std::string &in) : autor_{in} {};
    bool operator()(const std::pair<const Book, size_t> &lhs) const {
      if (lhs.first.get_autor() == autor_) {
        return true;
      } else {
        return false;
      }
    };
  };
  for (auto i{bookcase_.begin()};
       (i = std::find_if(i, bookcase_.end(), Comp{autor})) != bookcase_.end();
       retval.push_back(i), ++i) {
  }
  return retval;
}

void Library::show_all_books() const {
  for (auto &i : bookcase_) {
    std::cout << i.first << ' ' << i.second << std::endl;
  }
}

void Library::register_reader(const Reader &reader) {
  if (journal_.find(reader) == journal_.end()) {
    journal_.insert(std::make_pair(reader, std::list<Book>{}));
  } else {
    throw std::invalid_argument{"Library already has this reader"};
  }
  return;
}

void Library::register_reader(const std::string &name,
                              const std::string &surname) {
  register_reader(Reader{name, surname});
}

void Library::erase_reader(const Reader &reader) {
  journal_.erase(reader);
  return;
}

void Library::erase_reader(const std::string &name,
                           const std::string &surname) {
  erase_reader(Reader{name, surname});
}

std::pair<Journal::iterator, bool> Library::find_reader(const Reader &reader) {
  auto finded = journal_.find(reader);
  bool attribute = finded != journal_.end();
  return std::make_pair(finded, attribute);
}

std::pair<Journal::iterator, bool>
Library::find_reader(const std::string &name, const std::string &surname) {
  return find_reader(Reader{name, surname});
}

void Library::show_all_readers() const {
  for (auto &i : journal_) {
    std::cout << i.first << std::endl;
  }
  return;
}

void Library::show_readers_books(const Reader &reader) const {
  try {
    auto books = journal_.at(reader);
    for (auto &i : books) {
      std::cout << i << std::endl;
    }
  } catch (std::out_of_range &except) {
    std::invalid_argument{"Library haven't this reader"};
  }
  return;
}

void Library::give_book_reader(const Book &book, const Reader &reader) {
  if (!std::get<2>(find_book(book))) {
    throw std::invalid_argument{"Library haven't this book"};
  } else {
    std::list<Book> cur_reader_list;
    try {
      cur_reader_list = journal_.at(reader);
    } catch (std::out_of_range &except) {
      throw std::invalid_argument{"Library haven't this reader"};
    }
    if (cur_reader_list.size() < MAX_COUNT_IN_ONE_HAND()) {
      cur_reader_list.push_back(book);
      remove_book(book);
    } else {
      throw std::length_error{"Uper then limit"};
    }
  }
  return;
}

void Library::take_book_reader(const Book &book, const Reader &reader) {
  try {
    auto book_list = journal_.at(reader);
    if (std::find(book_list.begin(), book_list.end(), book) ==
        book_list.end()) {
      std::invalid_argument{"Reader don't have this book"};
    } else {
      book_list.remove(book);
      add_book(book);
    }
  } catch (std::out_of_range &except) {
    std::invalid_argument{"Library haven't this reader"};
  }
  return;
}
