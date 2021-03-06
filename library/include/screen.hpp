// screen.hpp

#pragma once

#include "library.hpp"
#include <QWidget>

class QTreeWidgetItem;

class Screen : public QWidget {
  Q_OBJECT
private:
  Library library_;

  ::QStringList comand_list_;
  ::QStringList operace_list_;

  Book cur_book_;
  Reader cur_reader_;

  std::pair<Bookcase::iterator, Bookcase::iterator> books_it_;
  std::pair<Journal::iterator, Journal::iterator> readers_it_;
  std::list<Bookcase::iterator> autor_books_;
  std::list<Book> reader_books_;

public:
  Screen();
  QPair<QString, QWidget *> create_bookcase_tab();
  QPair<QString, QWidget *> create_journal_tab();

private:
  void set_book(const Book &);
  void set_reader(const Reader &);
public slots:
  void for_books();
  void for_readers();
  void give_book();
  void take_book();
  void set_book(QTreeWidgetItem *);
  void set_reader(QTreeWidgetItem *);
signals:
  void book_rezult(const QString &);
  void reader_rezult(const QString &);
  void problem(const QString &);
  void book_in();
  void reader_in();
  void display_books();
  void display_readers();
  void display_autor();
  void display_reader_books();
};
