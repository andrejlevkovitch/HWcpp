// book.hpp

#pragma once

#include <cstdbool>
#include <iostream>
#include <string>

class Book {
private:
  std::string name_;
  std::string autor_;

public:
  Book();
  Book(const std::string &name, const std::string &autor);
  const std::string &get_name() const;
  const std::string &get_autor() const;
  bool operator<(const Book &) const;
  bool operator==(const Book &) const;
  bool operator!=(const Book &) const;
  friend std::ostream &operator<<(std::ostream &, const Book &);
};
