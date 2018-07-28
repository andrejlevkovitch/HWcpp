// main.cpp

#include <QApplication>
#include "editor.h"

int main(int argc, char *argv[]) {
  ::QApplication app(argc, argv);

  Editor editor;
  editor.show();

  return app.exec();
}
