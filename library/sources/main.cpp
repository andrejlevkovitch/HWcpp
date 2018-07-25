// main.cpp

#include "screen.hpp"
#include <QApplication>

int main(int argc, char *argv[]) {
  QApplication app(argc, argv);
  Screen screen;
  screen.setWindowTitle("Library");
  screen.setMinimumSize(250, 50);
  screen.show();
  return app.exec();
}