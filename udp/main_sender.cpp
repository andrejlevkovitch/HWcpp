// main.cpp

#include "udp_sender.hpp"
#include <QApplication>

int main(int argc, char *argv[]) {
  ::QApplication app(argc, argv);
  udp_sender sender{};
  sender.show();

  return app.exec();
}
