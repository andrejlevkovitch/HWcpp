// pars.cpp

#include "pars.hpp"

std::string pars(const std::string &text) {
  std::string out;
  out.reserve(text.size());
  for (auto i = text.begin(); i != text.end(); ++i) {
    if (*i == '/') {
      if (*std::next(i) == '/') {
        while (i != text.end() && *i != '\n') {
          ++i;
        }
        --i;
        continue;
      } else if (*std::next(i) == '*') {
        ++i;
        while (!(*std::prev(i) == '*' && *i == '/')) {
          ++i;
          if (i == text.end()) {
            out = "Error::Not founded */";
            --i;
            break;
          }
        }
        continue;
      }
    }
    if (!(*i == '\n' && (out.rbegin() == out.rend() || *out.rbegin() == '\n'))) {
      out += *i;
    }
  }
  return out;
}
