// udp_sender.hpp

#pragma once

#include <QWidget>

class QUdpSocket;
class QLineEdit;
class QSpinBox;
class QTextBrowser;

class udp_sender : public QWidget {
public:
  udp_sender(QWidget *parent = nullptr);

private:
  QUdpSocket *socket_;
  QLineEdit *adress_edit_;
  QSpinBox *port_number_;
  QLineEdit *message_;
  QTextBrowser *text_browser_;
};
