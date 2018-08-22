// server.hpp

#pragma once

#include <QWidget>

const int DEFAULT_PORT{2112};
const ::QString DEFAULT_HOST{"any"};

class QTcpServer;
class QTextEdit;
class QTcpSocket;

class Server : public ::QWidget {
  Q_OBJECT
private:
  ::QString host_;
  int port_;
  ::QTcpServer *server_;
  ::QTextEdit *text_edit_;

public:
  Server(::QWidget *parent = nullptr);
  void send_to_client(::QTcpSocket *socket, const ::QString &message) const;

public slots:
  void set_host_port_slot();
  void run_server();
  void new_connect_slot();
  void read_file();
};
