// library.cpp

#include "library.hpp"

#include <algorithm>
#include <exception>
#include <fstream>

Library::Library(const std::string &fileBook, const std::string &fileJournal)
    : file_bookcase_{fileBook}, file_journal_{fileJournal} {
  std::ifstream fin;
  fin.open(file_bookcase_, std::ios_base::in | std::ios_base::binary);
  if (fin.is_open()) {
    size_t size{};
    std::string name;
    std::string autor;
    while (true) {
      size = 0;
      fin.read(reinterpret_cast<char *>(&size), sizeof(size));
      name.resize(size);
      fin.read(reinterpret_cast<char *>(&name[0]), size);
      size = 0;
      fin.read(reinterpret_cast<char *>(&size), sizeof(size));
      autor.resize(size);
      fin.read(reinterpret_cast<char *>(&autor[0]), size);
      size = 0;
      fin.read(reinterpret_cast<char *>(&size), sizeof(unsigned short));
      if (fin.eof()) {
        break;
      }
      add_book(name, autor, size);
    }
    fin.close();
  }
  fin.open(file_journal_, std::ios_base::in | std::ios_base::binary);
  if (fin.is_open()) {
    size_t size{};
    std::string name;
    std::string surname;
    while (true) {
      size = 0;
      fin.read(reinterpret_cast<char *>(&size), sizeof(size));
      name.resize(size);
      fin.read(reinterpret_cast<char *>(&name[0]), size);
      size = 0;
      fin.read(reinterpret_cast<char *>(&size), sizeof(size));
      surname.resize(size);
      fin.read(reinterpret_cast<char *>(&surname[0]), size);
      size_t list_size{};
      fin.read(reinterpret_cast<char *>(&list_size), sizeof(list_size));
      if (fin.eof()) {
        break;
      }
      auto cur_reader = register_reader(name, surname).first;
      std::string book_name;
      std::string book_autor;
      for (int i = 0; i < list_size; ++i) {
        size = 0;
        fin.read(reinterpret_cast<char *>(&size), sizeof(size));
        book_name.resize(size);
        fin.read(reinterpret_cast<char *>(&book_name[0]), size);
        size = 0;
        fin.read(reinterpret_cast<char *>(&size), sizeof(size));
        book_autor.resize(size);
        fin.read(reinterpret_cast<char *>(&book_autor[0]), size);
        cur_reader->second.push_back(Book{book_name, book_autor});
      }
    }
    fin.close();
  }
}

Library::~Library() {
  std::ofstream fout;
  fout.open(file_bookcase_, std::ios_base::out | std::ios_base::binary);
  if (fout.is_open()) {
    size_t size{};
    for (const auto &i : bookcase_) {
      size = i.first.get_name().size();
      fout.write(reinterpret_cast<char *>(&size), sizeof(size));
      fout.write(i.first.get_name().c_str(), size);
      size = i.first.get_autor().size();
      fout.write(reinterpret_cast<char *>(&size), sizeof(size));
      fout.write(i.first.get_autor().c_str(), size);
      size = i.second;
      fout.write(reinterpret_cast<char *>(&size), sizeof(unsigned short));
    }
    fout.close();
  }
  fout.open(file_journal_, std::ios_base::out | std::ios_base::binary);
  if (fout.is_open()) {
    size_t size{};
    for (const auto &i : journal_) {
      size = i.first.get_name().size();
      fout.write(reinterpret_cast<char *>(&size), sizeof(size));
      fout.write(i.first.get_name().c_str(), size);
      size = i.first.get_surname().size();
      fout.write(reinterpret_cast<char *>(&size), sizeof(size));
      fout.write(i.first.get_surname().c_str(), size);
      size = i.second.size();
      fout.write(reinterpret_cast<char *>(&size), sizeof(size));
      for (const auto &j : i.second) {
        size = j.get_name().size();
        fout.write(reinterpret_cast<char *>(&size), sizeof(size));
        fout.write(j.get_name().c_str(), size);
        size = j.get_autor().size();
        fout.write(reinterpret_cast<char *>(&size), sizeof(size));
        fout.write(j.get_autor().c_str(), size);
      }
    }
    fout.close();
  }
}

unsigned short Library::MAX_COUNT_IN_ONE_HAND() {
  static unsigned short retval{5};
  return retval;
}

void Library::add_book(const Book &book, unsigned short count) {
  auto finded = find_book(book);
  if (std::get<2>(finded)) {
    std::get<0>(finded)->second += count;
  } else {
    bookcase_.insert(std::make_pair(book, count));
  }
  return;
}

void Library::add_book(const std::string &name, const std::string &autor,
                       unsigned short count) {
  add_book(Book{name, autor}, count);
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

std::pair<Journal::iterator, bool>
Library::register_reader(const Reader &reader) {
  return journal_.insert(std::make_pair(reader, std::list<Book>{}));
}

std::pair<Journal::iterator, bool>
Library::register_reader(const std::string &name, const std::string &surname) {
  return register_reader(Reader{name, surname});
}

bool Library::erase_reader(const Reader &reader) {
  return journal_.erase(reader);
}

bool Library::erase_reader(const std::string &name,
                           const std::string &surname) {
  return erase_reader(Reader{name, surname});
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

void Library::give_book_reader(const Book &book, const Reader &reader) {
  auto finded = find_book(book);
  if (!std::get<2>(finded)) {
    throw std::invalid_argument{"Library hasn't this book"};
  } else {
    try {
      auto &cur_reader_list = journal_.at(reader);
      if (cur_reader_list.size() < MAX_COUNT_IN_ONE_HAND()) {
        cur_reader_list.push_back(std::get<0>(finded)->first);
        remove_book(std::get<0>(finded)->first);
      } else {
        throw std::length_error{"Upper then limit"};
      }
    } catch (std::out_of_range &except) {
      throw std::invalid_argument{"Library hasn't this reader"};
    }
  }
  return;
}

void Library::take_book_reader(const Book &book, const Reader &reader) {
  try {
    auto &book_list = journal_.at(reader);
    std::list<Book>::iterator finded;

    if (book.get_autor().empty() && (std::count(book_list.begin(), book_list.end(), book) > 1)) {
      throw std::invalid_argument{"Reader has several books whith this name"};
    }
    if ((finded = std::find(book_list.begin(), book_list.end(), book)) ==
        book_list.end()) {
      throw std::invalid_argument{"Reader hasn't this book"};
    } else {
      add_book(*finded);
      book_list.erase(finded);
    }
  } catch (std::out_of_range &except) {
    throw std::invalid_argument{"Library hasn't this reader"};
  }
  return;
}

size_t Library::getBooksNum() const { return bookcase_.size(); }

size_t Library::getReadersNum() const { return journal_.size(); }

std::pair<Bookcase::iterator, Bookcase::iterator> Library::first_last_book() {
  return std::make_pair(bookcase_.begin(), bookcase_.end());
}

std::pair<Journal::iterator, Journal::iterator> Library::first_last_reader() {
  return std::make_pair(journal_.begin(), journal_.end());
}
