// cs.hpp

#include <QWidget>

const int default_port{2112};

class QTextEdit;
class QTcpServer;
class QTcpSocket;

class CS : public ::QWidget {
  Q_OBJECT
private:
  ::QTcpServer *server_;
  ::QTcpSocket *socket_;
  ::QTextEdit *text_edit_;
  ::QString host_;

public:
  CS(::QWidget *parent = nullptr);

private slots:
  void send_message();
  void read_message();
  void listen_slot();
  void connect_slot();
  void set_socket();
};
