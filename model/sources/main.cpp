// main.cpp

#include "model.h"
#include "model_reader.h"
#include <QApplication>
#include <QTreeView>

int main(int argc, char *argv[]) {
  ::QApplication app(argc, argv);
  Library library{"../data/bookcase.txt", "../data/journal.txt"};
  Model model{&library.bookcase_};
  ModelReader model2{library.journal_};
  ::QTreeView list;
  list.setModel(&model);
  list.show();
//::QTreeView list2;
//list2.setModel(&model2);
//list2.show();

  return app.exec();
}
