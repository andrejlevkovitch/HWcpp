// screen.hpp

#pragma once

#include "library.hpp"
#include <QWidget>

class Screen : public QWidget {
  Q_OBJECT
private:
  Library library_;

  ::QStringList comand_list_;

  ::QString book_name_;
  ::QString book_autor_;
  ::QString reader_name_;
  ::QString reader_surname_;

public:
  Screen();
private:
public slots:
  void for_books();
//void set_book_name(const QString &);
//void set_book_autor(const QString &);
signals:
  void rezult(const QString &);
};
