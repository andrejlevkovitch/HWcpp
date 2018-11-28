// udp_reciver.hpp

#pragma once

#include <QWidget>

class QUdpSocket;
class QTextBrowser;
class QLineEdit;
class QSpinBox;

class udp_reciver : public QWidget {
  Q_OBJECT
public:
  udp_reciver(QWidget *parent = nullptr);

private:
  QUdpSocket *socket_;
  QTextBrowser *text_browser_;
  QLineEdit *adress_edit_;
  QSpinBox *port_number_;
};
