// main.cpp

#include "udp_reciver.hpp"
#include <QApplication>

int main(int argc, char *argv[]) {
  ::QApplication app(argc, argv);
  udp_reciver reciver{};
  reciver.show();

  return app.exec();
}
