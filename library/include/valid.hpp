// valid.hpp

#pragma once

#include <QValidator>

class Valid : public QValidator {
public:
  Valid(QObject *parent);
  virtual State validate(QString &str, int &) const;
};
