// udp_sender.hpp

#include "udp_sender.hpp"
#include <QLineEdit>
#include <QSpinBox>
#include <QTextBrowser>
#include <QUdpSocket>
#include <QVBoxLayout>

udp_sender::udp_sender(QWidget *parent)
    : QWidget{parent}, socket_{new QUdpSocket}, adress_edit_{new QLineEdit},
      port_number_{new QSpinBox}, message_{new QLineEdit},
      text_browser_{new QTextBrowser} {
  this->setWindowTitle("UDP sender");
  port_number_->setMaximum(100000);
  auto v_layout = new QVBoxLayout{this};
  v_layout->addWidget(text_browser_);
  v_layout->addWidget(port_number_);
  v_layout->addWidget(adress_edit_);
  v_layout->addWidget(message_);
  connect(message_, &QLineEdit::returnPressed, this, [=]() {
    socket_->writeDatagram(
        message_->text().toStdString().c_str(), message_->text().size(),
        ::QHostAddress{adress_edit_->text()}, port_number_->value());
    text_browser_->append("\nsend message: " + message_->text());
  });
  this->setLayout(v_layout);
}
