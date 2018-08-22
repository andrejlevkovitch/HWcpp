// main.cpp

#include <QApplication>
#include "server.hpp"

int main(int argc, char *argv[]) {
  ::QApplication app(argc, argv);
  Server server;
  server.show();

  return app.exec();
}
