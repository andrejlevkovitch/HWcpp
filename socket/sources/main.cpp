// main.cpp

#include <QApplication>
#include "cs.hpp"

int main(int argc, char *argv[]) {
  ::QApplication app(argc, argv);
  CS cs;
  cs.show();

  return app.exec();
}
