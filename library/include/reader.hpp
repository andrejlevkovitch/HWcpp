// reader.hpp

#pragma once

#include <cstdbool>
#include <iostream>
#include <string>

class Reader {
private:
  std::string name_;
  std::string surname_;

public:
  Reader();
  Reader(const std::string &name, const std::string &surname);
  const std::string &get_name() const;
  const std::string &get_surname() const;
  bool operator<(const Reader &) const;
  bool operator==(const Reader &) const;
  bool operator!=(const Reader &) const;
  friend std::ostream &operator<<(std::ostream &, const Reader &);
};
