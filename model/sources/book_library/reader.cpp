// reader.cpp

#include "reader.hpp"
#include <algorithm>
#include <cctype>

Reader::Reader() : name_{}, surname_{} {}

Reader::Reader(const std::string &name, const std::string &surname) {
  name_.resize(name.size());
  surname_.resize(surname.size());
  std::transform(name.begin(), name.end(), name_.begin(), toupper);
  std::transform(surname.begin(), surname.end(), surname_.begin(), toupper);
}

const std::string &Reader::get_name() const { return name_; }

const std::string &Reader::get_surname() const { return surname_; }

bool Reader::operator<(const Reader &rhs) const {
  if (surname_ < rhs.surname_) {
    return true;
  } else if (surname_ == rhs.surname_ && name_ < rhs.name_) {
    return true;
  } else {
    return false;
  }
}

bool Reader::operator==(const Reader &rhs) const {
  return (surname_ == rhs.surname_ && name_ == rhs.name_);
}

bool Reader::operator!=(const Reader &rhs) const {
  return (surname_ != rhs.surname_ || name_ != rhs.name_);
}

std::ostream &operator<<(std::ostream &out, const Reader &reader) {
  out << reader.name_ << ' ' << reader.surname_;
  return out;
}
