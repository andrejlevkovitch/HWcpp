// udp_server.cpp

#include "udp_reciver.hpp"
#include <QLineEdit>
#include <QSpinBox>
#include <QTextBrowser>
#include <QUdpSocket>
#include <QVBoxLayout>

udp_reciver::udp_reciver(QWidget *parent)
    : QWidget{parent}, socket_{new ::QUdpSocket{this}},
      text_browser_{new QTextBrowser{this}}, adress_edit_{new QLineEdit{this}},
      port_number_{new QSpinBox{this}} {
  this->setWindowTitle("UDP reciver");
  port_number_->setMaximum(100000);
  adress_edit_->setPlaceholderText("Ip");
  auto v_layout = new QVBoxLayout{this};
  v_layout->addWidget(text_browser_);
  v_layout->addWidget(port_number_);
  v_layout->addWidget(adress_edit_);
  connect(adress_edit_, &QLineEdit::returnPressed, this, [=]() {
    if (socket_->bind(::QHostAddress{adress_edit_->text()},
                      port_number_->value())) {
      text_browser_->append("bind to: " + adress_edit_->text() + ":" +
                            QString::number(port_number_->value()));
    } else {
      text_browser_->append("fail bind to: " + adress_edit_->text() + ":" +
                            QString::number(port_number_->value()));
    }
  });
  connect(socket_, &QUdpSocket::readyRead, this, [=]() {
    text_browser_->append("\nnew message: ");
    std::string message;
    message.resize(1000);
    socket_->readDatagram(&message[0], 1000);
    text_browser_->append(QString(message.c_str()));
  });
  this->setLayout(v_layout);
}
