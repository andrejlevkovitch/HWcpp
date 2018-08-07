// main.cpp

#include <QApplication>
#include "screen.hpp"

int main(int argc, char *argv[]) {
  ::QApplication app(argc, argv);
  painter::screen painter;
  painter.show();

  return app.exec();
}
