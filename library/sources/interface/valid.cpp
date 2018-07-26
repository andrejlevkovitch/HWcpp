//valid.cpp

#include <QtWidgets>
#include "valid.hpp"

Valid::Valid(QObject *parent) : ::QValidator(parent) {
}

auto Valid::validate(QString &str, int &pos) const -> State {
  ::QRegExp not_valid_values{"[^ -~]"};//{"[^A-Za-z0-9]"};
  if (str.contains(not_valid_values)) {
    return Invalid;
  }
  return Acceptable;
}
