// screen.cpp

#include "screen.hpp"
#include <QtWidgets>

Screen::Screen()
    : QWidget{}, library_{"../data/bookcase.txt", "..data/journal.txt"} {
  ::QList<::QPair<QString, QWidget *>> widget_list;

  comand_list_ << "Find"
               << "Add"
               << "Remove";

  for (auto &i : comand_list_) {
    widget_list.push_back(::qMakePair(i, new QWidget));

    ::QLabel *rezult = new ::QLabel;
    connect(this, SIGNAL(rezult(const QString &)), rezult,
            SLOT(setText(const QString &)));
    rezult->setFrameStyle(QFrame::Box | QFrame::Raised);
    rezult->setFixedHeight(50);
    rezult->setLineWidth(2);

    ::QLabel *name = new ::QLabel("&Name");
    ::QLineEdit *name_field = new ::QLineEdit;
    name->setBuddy(name_field);
    ::QVBoxLayout *name_layout = new ::QVBoxLayout;
    name_layout->addWidget(name);
    name_layout->addWidget(name_field);

    ::QLabel *autor = new ::QLabel("&Autor");
    ::QLineEdit *autor_field = new ::QLineEdit;
    autor->setBuddy(autor_field);
    ::QVBoxLayout *autor_layout = new ::QVBoxLayout;
    autor_layout->addWidget(autor);
    autor_layout->addWidget(autor_field);

    ::QHBoxLayout *find_layout = new ::QHBoxLayout;
    find_layout->addLayout(name_layout);
    find_layout->addLayout(autor_layout);

    ::QPushButton *execute = new ::QPushButton(i);
    connect(execute, &QPushButton::clicked, [=]() {
      book_name_ = name_field->text();
      book_autor_ = autor_field->text();
    });
    connect(execute, SIGNAL(clicked()), SLOT(for_books()));
    ::QVBoxLayout *general_layout = new ::QVBoxLayout;
    general_layout->addWidget(rezult);
    general_layout->addLayout(find_layout);
    general_layout->addWidget(execute);

    widget_list.last().second->setLayout(general_layout);
  }

  ::QTabWidget *tab_wdg = new ::QTabWidget;
  for (auto &i : widget_list) {
    tab_wdg->addTab(i.second, i.first);
  }

  ::QHBoxLayout *general_layout = new ::QHBoxLayout;
  general_layout->addWidget(tab_wdg);
  setLayout(general_layout);
};

void Screen::for_books() {
  ::QString retval;
  auto comand = reinterpret_cast<::QPushButton *>(sender())->text();
  if (comand == comand_list_[0]) {
    if (book_name_.isEmpty() && book_autor_.isEmpty()) {
      retval = "Input datas, please";
    } else if (book_name_.isEmpty()) {
      auto finded = library_.find_autor(book_autor_.toStdString());
      if (finded.empty()) {
        retval = "Library hasn't books of this autor";
      } else if (finded.size() == 1) {
        retval = "Library has only one book of this autor";
      } else {
        retval = "Library has " + retval.setNum(finded.size()) + " books of this autor";
      }
    } else {
      auto finded = library_.find_book(book_name_.toStdString(),
                                       book_autor_.toStdString());
      if (std::get<2>(finded)) {
        retval = "We have one";
      } else if (std::get<0>(finded) == std::get<1>(finded)) {
        retval = "Library hasn't this";
      } else {
        retval = "Library has " +
                 retval.setNum(
                     std::distance(std::get<0>(finded), std::get<1>(finded))) +
                 " books with this name.";
      }
    }
  } else if (comand == comand_list_[1]) {
    if (book_name_.isEmpty() || book_autor_.isEmpty()) {
      retval = "Input data, please";
    } else {
      library_.add_book(book_name_.toStdString(), book_autor_.toStdString());
      retval = "Executed";
    }
  } else if (comand == comand_list_[2]) {
    if (book_name_.isEmpty()) {
      retval = "Input data, please";
    } else {
      if (library_.remove_book(book_name_.toStdString(),
                               book_autor_.toStdString())) {
        retval = "Executed";
      } else {
        retval = "Not removed";
      }
    }
  }
  emit rezult(retval);
}
