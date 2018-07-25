// book.cpp

#include "book.hpp"

Book::Book() : name_{}, autor_{} {}

Book::Book(const std::string &name, const std::string &autor)
    : name_{name}, autor_{autor} {}

const std::string &Book::get_name() const {
  return name_;
}

const std::string &Book::get_autor() const {
  return autor_;
}

bool Book::operator<(const Book &rhs) const {
  if (name_ < rhs.name_) {
    return true;
  } else {
    return false;
  }
}

bool Book::operator==(const Book &rhs) const {
  return (name_ == rhs.name_);
}

bool Book::operator!=(const Book &rhs) const {
  return (name_ != rhs.name_);
}

std::ostream &operator<<(std::ostream &out, const Book &book) {
  out << book.name_ << ' ' << book.autor_;
  return out;
}
