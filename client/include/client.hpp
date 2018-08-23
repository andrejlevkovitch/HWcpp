// client.hpp

#pragma once

#include <QWidget>

const ::QString DEFAULT_HOST{"localhost"};
const int DEFAULT_PORT{2112};
const int MAX_LEN_BUF{4000};

class QTcpSocket;
class QTextEdit;
class QLineEdit;

class Client : public ::QWidget {
  Q_OBJECT
private:
  ::QTcpSocket *socket_;
  ::QTextEdit *text_edit_;
  ::QString host_;
  int port_;

public:
  Client(::QWidget *parent = nullptr);

  public slots:
    void run_client();
    void set_host_port_slot();
    void send_file();
};
