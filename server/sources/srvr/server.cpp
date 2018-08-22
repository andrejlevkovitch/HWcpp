// server.cpp

#include "server.hpp"
#include <QAction>
#include <QBoxLayout>
#include <QDomDocument>
#include <QFile>
#include <QInputDialog>
#include <QMimeData>
#include <QTcpServer>
#include <QTcpSocket>
#include <QTextEdit>
#include <QTextStream>
#include <QToolBar>

Server::Server(::QWidget *parent)
    : ::QWidget{parent}, host_{DEFAULT_HOST}, port_{DEFAULT_PORT},
      server_{nullptr}, text_edit_{nullptr} {
  server_ = new ::QTcpServer{this};
  connect(server_, SIGNAL(newConnection()), this, SLOT(new_connect_slot()));

  auto general_layout = new ::QVBoxLayout;
  {
    auto tool_bar = new ::QToolBar;
    {
      auto set_host_port_action = new ::QAction{"host and port", tool_bar};
      connect(set_host_port_action, SIGNAL(triggered()), this,
              SLOT(set_host_port_slot()));

      tool_bar->addAction(set_host_port_action);
    }

    text_edit_ = new ::QTextEdit;
    text_edit_->setReadOnly(true);
    text_edit_->append("Server created");

    general_layout->addWidget(tool_bar);
    general_layout->addWidget(text_edit_);
  }
  this->setLayout(general_layout);
  run_server();
}

void Server::send_to_client(::QTcpSocket *socket,
                            const ::QString &message) const {
  socket->write(message.toUtf8());
}

void Server::set_host_port_slot() {
  bool host_on{false};
  bool port_on{false};

  auto host = ::QInputDialog::getText(
      nullptr, "input", "host", ::QLineEdit::EchoMode::Normal, host_, &host_on);

  auto port = ::QInputDialog::getInt(nullptr, "input", "port", port_, 2000,
                                     8000, 1, &port_on);
  if (host_on) {
    host_ = host;
  }
  if (port_on) {
    port_ = port;
  }
  if (host_on || port_on) {
    run_server();
  }
}

void Server::run_server() {
  server_->close();
  if (!server_->listen(::QHostAddress{} = host_, port_)) {
    text_edit_->append("SERVER_ERROR!!!");
    server_->close();
    return;
  }
  text_edit_->append("Host set: " + host_ + "\nPort set: " +
                     ::QString::number(port_) + "\nServer run");
}

void Server::new_connect_slot() {
  auto socket = server_->nextPendingConnection();
  connect(socket, SIGNAL(disconnected()), socket, SLOT(deleteLater()));
  connect(socket, &::QTcpSocket::disconnected, text_edit_,
          [=]() { text_edit_->append("Client DISCONNECTED"); });
  connect(socket, SIGNAL(readyRead()), this, SLOT(read_file()));

  send_to_client(socket, "Server response : CONNECTED");
  text_edit_->append("NEW CONNECTION");
}

void Server::read_file() {
  auto socket = dynamic_cast<::QTcpSocket *>(sender());
  ::QDomDocument dom_doc;
  ::QTextStream stream{socket};
  dom_doc.setContent(stream.readAll());
  send_to_client(socket, "OK");
  auto dom_element = dom_doc.documentElement();
  if (!dom_element.isNull()) {
    if (dom_element.tagName() == "file") {
      auto file_name = dom_element.attribute("name");
      auto file_size = dom_element.attribute("size").toUInt();
      auto number = dom_element.attribute("number").toUInt();

      ::QFile file{file_name};
      if (number) {
        if (file.exists()) {
          file.open(::QIODevice::Append);
        } else {
          text_edit_->append("Error of file recive");
          return;
        }
      } else {
        if (file.exists()) {
          text_edit_->append("File with this name already exists");
          return;
        }
        file.open(::QIODevice::WriteOnly);
      }
      if (file.isOpen()) {
        if (file.size() >= file_size) {
          return;
        }
        auto barr = dom_element.text().toUtf8();
        file.write(::QByteArray::fromBase64(barr));
        if (file.size() == file_size) {
          text_edit_->append("File " + file_name + " received");
        }
        file.close();
      }
    }
  }
}
