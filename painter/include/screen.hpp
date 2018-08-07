// screen.hpp

#pragma once

#include <QWidget>

class MouseEvent;
class QPaintEvent;

namespace painter {
class screen : public ::QWidget {
  Q_OBJECT
private:
public:
  screen(::QWidget *parent = nullptr);

signals:
  void send_open_file(const ::QString &);
  void send_save_file(const ::QString &);
};
};
