// cs.cpp

#include "cs.hpp"
#include <QBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QTcpServer>
#include <QTcpSocket>
#include <QTextEdit>
#include <QtGlobal>

CS::CS(::QWidget *parent)
    : ::QWidget{parent}, server_{nullptr}, socket_{nullptr}, text_edit_{
                                                                 nullptr} {
  auto general_layout = new ::QVBoxLayout;
  {
    text_edit_ = new ::QTextEdit;
    text_edit_->setReadOnly(true);

    auto line_layout = new ::QHBoxLayout;
    {
      auto line_edit = new ::QLineEdit;
      connect(line_edit, SIGNAL(returnPressed()), this, SLOT(send_message()));
      auto send_button = new ::QPushButton{"send"};
      connect(send_button, SIGNAL(clicked()), line_edit,
              SIGNAL(returnPressed()));

      line_layout->addWidget(line_edit);
      line_layout->addWidget(send_button);
    }
    auto connect_wgt = new ::QWidget;
    auto connecting_layout = new ::QHBoxLayout;
    {
      auto ip_edit = new ::QLineEdit;
      connect(ip_edit, SIGNAL(returnPressed()), this, SLOT(connect_slot()));

      auto connect_button = new ::QPushButton{"connect"};
      connect(connect_button, SIGNAL(clicked()), ip_edit,
              SIGNAL(returnPressed()));

      auto listen_button = new ::QPushButton{"listen"};
      connect(listen_button, SIGNAL(clicked()), this, SLOT(listen_slot()));
      connect(listen_button, SIGNAL(clicked()), connect_wgt, SLOT(hide()));

      connecting_layout->addWidget(ip_edit);
      connecting_layout->addWidget(connect_button);
      connecting_layout->addWidget(listen_button);
    }
    connect_wgt->setLayout(connecting_layout);
    general_layout->addWidget(text_edit_);
    general_layout->addLayout(line_layout);
    general_layout->addWidget(connect_wgt);
  }
  this->setLayout(general_layout);
}

void CS::send_message() {
  auto line_edit = dynamic_cast<::QLineEdit *>(sender());
  Q_CHECK_PTR(line_edit);
  text_edit_->append("ME: " + line_edit->text());
  if (socket_) {
    socket_->write(line_edit->text().toUtf8());
  }
  line_edit->clear();
}

void CS::read_message() { text_edit_->append("UM: " + socket_->readAll()); }

void CS::listen_slot() {
  if (!server_) {
    text_edit_->append("__SERVER__");
    server_ = new ::QTcpServer{this};
    server_->listen(::QHostAddress::Any, default_port);
    connect(server_, SIGNAL(newConnection()), this, SLOT(set_socket()));
  }
}

void CS::connect_slot() {
  auto line_edit = dynamic_cast<::QLineEdit *>(sender());
  Q_CHECK_PTR(line_edit);
  if (!socket_) {
    text_edit_->append("__CLIENT__");
    socket_ = new ::QTcpSocket{this};
    connect(socket_, &::QTcpSocket::connected, text_edit_,
            [=]() { text_edit_->append("CONNECTED"); });
    connect(socket_, SIGNAL(readyRead()), this, SLOT(read_message()));
  }
  socket_->connectToHost(line_edit->text(), default_port);
}

void CS::set_socket() {
  if (!socket_) {
    text_edit_->append("CONNECTED");
    socket_ = server_->nextPendingConnection();
    connect(socket_, SIGNAL(disconnected()), socket_, SLOT(deleteLater()));
    connect(socket_, &::QTcpSocket::disconnected, text_edit_,
            [=]() { text_edit_->append("DISCONNECTED"); });
    connect(socket_, SIGNAL(readyRead()), this, SLOT(read_message()));
  } else {
    text_edit_->append("CONNECTION ATTEMPT");
  }
}
