// client.cpp

#include "client.hpp"
#include <QBoxLayout>
#include <QBuffer>
#include <QByteArray>
#include <QDomDocument>
#include <QFileDialog>
#include <QHostAddress>
#include <QInputDialog>
#include <QLineEdit>
#include <QMimeData>
#include <QTcpSocket>
#include <QTextEdit>
#include <QToolBar>

Client::Client(::QWidget *parent)
    : ::QWidget{parent}, socket_{nullptr},
      text_edit_{nullptr}, host_{DEFAULT_HOST}, port_{DEFAULT_PORT} {
  socket_ = new ::QTcpSocket{this};
  connect(socket_, &::QTcpSocket::connected, text_edit_,
          [=]() { text_edit_->append("CONNECTED WITH SERVER"); });

  auto general_layout = new ::QVBoxLayout;
  {
    auto tool_bar = new ::QToolBar;
    {
      auto set_host_port_action = new ::QAction{"host and port", tool_bar};
      connect(set_host_port_action, SIGNAL(triggered()), this,
              SLOT(set_host_port_slot()));

      auto send_file_action = new ::QAction{"send file", tool_bar};
      connect(send_file_action, SIGNAL(triggered()), this, SLOT(send_file()));

      tool_bar->addAction(set_host_port_action);
      tool_bar->addAction(send_file_action);
    }

    text_edit_ = new ::QTextEdit;
    text_edit_->setReadOnly(true);
    text_edit_->append("Client created");

    general_layout->addWidget(tool_bar);
    general_layout->addWidget(text_edit_);
  }
  this->setLayout(general_layout);
  run_client();
}

void Client::run_client() {
  socket_->close();
  socket_->connectToHost(host_, port_);
  text_edit_->append("Host set: " + host_ + "\nPort set: " +
                     ::QString::number(port_) + "\nClient runed");
}

void Client::set_host_port_slot() {
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
    run_client();
  }
}

void Client::send_file() {
  auto file_path = ::QFileDialog::getOpenFileName(nullptr, "Send", ".");
  if (!file_path.isNull()) {
    ::QFile file{file_path};
    if (file.open(::QFile::ReadOnly)) {
      auto file_name = file_path.section('/', -1);
      auto size = file.size();
      unsigned number{};

      do {
        auto barr = file.read(MAX_LEN_BUF);
        barr = barr.toBase64();

        ::QDomDocument dom_doc{"date"};
        auto dom_element = dom_doc.createElement("file");
        {
          auto name_attr = dom_doc.createAttribute("name");
          name_attr.setValue(file_name);

          auto size_attr = dom_doc.createAttribute("size");
          size_attr.setValue(::QString::number(size));

          auto number_attr = dom_doc.createAttribute("number");
          number_attr.setValue(::QString::number(number));
          ++number;

          auto dom_date = dom_doc.createTextNode(barr);

          dom_element.setAttributeNode(name_attr);
          dom_element.setAttributeNode(size_attr);
          dom_element.setAttributeNode(number_attr);
          dom_element.appendChild(dom_date);
        }
        dom_doc.appendChild(dom_element);

        auto data = dom_doc.toByteArray();
        socket_->write(data);
        socket_->flush();
        //вот сдесь, почему-то иногда вместо отправки одного пакета  данных,
        //происходит отправка сразу двух пакетов в одном.

        //      socket_->waitForReadyRead();//если раскоментировать эту строку,
        //      то вся проблема исчезнет, так как нужен ответ от сервера

        text_edit_->append("send " + ::QString::number(number) + " packet " +
                           ::QString::number(data.size()) + " byte");
        socket_->readAll();

      } while (!file.atEnd());

      file.close();
    }
  }
}
