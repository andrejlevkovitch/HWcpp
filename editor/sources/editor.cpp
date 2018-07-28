// editor.cpp

#include "editor.h"
#include "pars.hpp"
#include <QBoxLayout>
#include <QPushButton>
#include <QTextEdit>

#include <string>

Editor::Editor(::QWidget *in) : ::QWidget(in) {
  ::QTextEdit *lhs = new ::QTextEdit;
  ::QTextEdit *rhs = new ::QTextEdit;
  rhs->setReadOnly(true);
  rhs->setPlaceholderText("output");
  lhs->setPlaceholderText("input");

  ::QPushButton *execute = new ::QPushButton("execute");
  connect(execute, &QPushButton::clicked, rhs, [=]() {
    rhs->setText(pars(lhs->toPlainText().toStdString()).c_str());
  });

  ::QHBoxLayout *general_layout = new ::QHBoxLayout;
  general_layout->addWidget(lhs);
  general_layout->addWidget(execute);
  general_layout->addWidget(rhs);
  setLayout(general_layout);
}
