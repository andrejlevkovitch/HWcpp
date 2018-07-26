// screen.cpp

#include "screen.hpp"
#include "valid.hpp"
#include <QtWidgets>

Screen::Screen()
    : QWidget{}, library_{"../data/bookcase.txt", "../data/journal.txt"} {
  ::QList<::QPair<QString, QWidget *>> widget_list;

  comand_list_ << "Find"
               << "Add"
               << "Remove";

  operace_list_ << "give"
                << "take away";

  ::QLabel *book = new ::QLabel{"Book"};
  ::QLabel *book_info = new ::QLabel;
  book_info->setFixedHeight(50);
  book_info->setFrameStyle(::QFrame::Box | ::QFrame::Raised);
  book_info->setLineWidth(2);
  ::QString capacity;
  capacity =
      "Library have " + capacity.setNum(library_.getBooksNum()) + " books now";
  book_info->setText(capacity);
  connect(this, SIGNAL(problem(const QString &)), book_info,
          SLOT(setText(const QString &)));
  connect(this, &Screen::book_in, book_info, [=]() {
    ::QString text = cur_book_.get_name().c_str();
    text += ", ";
    text += cur_book_.get_autor().c_str();
    book_info->setText(text);
  });
  book->setBuddy(book_info);

  ::QLabel *reader = new ::QLabel{"Reader"};
  ::QLabel *reader_info = new ::QLabel;
  capacity = "Library have " + capacity.setNum(library_.getReadersNum()) +
             " readers now";
  reader_info->setText(capacity);
  reader_info->setFixedHeight(50);
  reader_info->setFrameStyle(::QFrame::Box | ::QFrame::Raised);
  reader_info->setLineWidth(2);
  connect(this, &Screen::reader_in, reader_info, [=]() {
    ::QString text = cur_reader_.get_name().c_str();
    text += ' ';
    text += cur_reader_.get_surname().c_str();
    reader_info->setText(text);
  });
  reader->setBuddy(reader_info);

  ::QPushButton *give = new ::QPushButton{operace_list_[0]};
  connect(give, SIGNAL(clicked()), SLOT(give_book()));
  connect(give, SIGNAL(clicked()), SLOT(for_books()));
  connect(give, SIGNAL(clicked()), SLOT(for_readers()));
  ::QPushButton *take = new ::QPushButton{operace_list_[1]};
  connect(take, SIGNAL(clicked()), SLOT(take_book()));
  connect(take, SIGNAL(clicked()), SLOT(for_books()));
  connect(take, SIGNAL(clicked()), SLOT(for_readers()));
  ::QHBoxLayout *buttons_layout = new ::QHBoxLayout;
  buttons_layout->addWidget(give);
  buttons_layout->addWidget(take);

  widget_list.push_back(create_bookcase_tab());
  widget_list.push_back(create_journal_tab());

  ::QTabWidget *tab_wgt = new ::QTabWidget;
  for (auto &i : widget_list) {
    tab_wgt->addTab(i.second, i.first);
  }

  ::QVBoxLayout *general_layout = new ::QVBoxLayout;
  general_layout->addWidget(book);
  general_layout->addWidget(book_info);
  general_layout->addWidget(reader);
  general_layout->addWidget(reader_info);
  general_layout->addLayout(buttons_layout);
  general_layout->addWidget(tab_wgt);
  setLayout(general_layout);
};

::QPair<::QString, ::QWidget *> Screen::create_journal_tab() {
  auto retval = ::qMakePair(::QString{"Journal"}, new QWidget);
  ::QLabel *rezult = new ::QLabel;
  connect(this, SIGNAL(reader_rezult(const QString &)), rezult,
          SLOT(setText(const QString &)));
  rezult->setFrameStyle(QFrame::Box | QFrame::Raised);
  rezult->setFixedHeight(50);
  rezult->setLineWidth(2);

  ::QLabel *name = new ::QLabel("&Name*");
  ::QLineEdit *name_field = new ::QLineEdit;
  Valid *name_valid = new Valid(name_field);
  name_field->setValidator(name_valid);
  name->setBuddy(name_field);
  ::QVBoxLayout *name_layout = new ::QVBoxLayout;
  name_layout->addWidget(name);
  name_layout->addWidget(name_field);

  ::QLabel *surname = new ::QLabel("&Surname*");
  ::QLineEdit *surname_field = new ::QLineEdit;
  Valid *surname_valid = new Valid(surname_field);
  surname_field->setValidator(surname_valid);
  surname->setBuddy(surname_field);
  ::QVBoxLayout *surname_layout = new ::QVBoxLayout;
  surname_layout->addWidget(surname);
  surname_layout->addWidget(surname_field);

  ::QHBoxLayout *reader_layout = new ::QHBoxLayout;
  reader_layout->addLayout(name_layout);
  reader_layout->addLayout(surname_layout);

  ::QHBoxLayout *button_layout = new ::QHBoxLayout;
  for (const auto &j : comand_list_) {
    ::QPushButton *execute = new ::QPushButton(j);
    connect(execute, &QPushButton::clicked, [=]() {
      set_reader(Reader{name_field->text().toStdString(),
                           surname_field->text().toStdString()});
    });
    connect(execute, SIGNAL(clicked()), SLOT(for_readers()));
    button_layout->addWidget(execute);
  }
  ::QVBoxLayout *general_layout = new ::QVBoxLayout;
  general_layout->addWidget(rezult);
  general_layout->addLayout(reader_layout);
  general_layout->addLayout(button_layout);

  retval.second->setLayout(general_layout);

  return retval;
}

::QPair<::QString, ::QWidget *> Screen::create_bookcase_tab() {
  auto retval = ::qMakePair(::QString{"Bookcase"}, new QWidget);
  ::QLabel *rezult = new ::QLabel;
  connect(this, SIGNAL(book_rezult(const QString &)), rezult,
          SLOT(setText(const QString &)));
  rezult->setFrameStyle(QFrame::Box | QFrame::Raised);
  rezult->setFixedHeight(50);
  rezult->setLineWidth(2);

  ::QLabel *name = new ::QLabel("&Name");
  ::QLineEdit *name_field = new ::QLineEdit;
  Valid *name_valid = new Valid(name_field);
  name_field->setValidator(name_valid);
  name->setBuddy(name_field);
  ::QVBoxLayout *name_layout = new ::QVBoxLayout;
  name_layout->addWidget(name);
  name_layout->addWidget(name_field);

  ::QLabel *autor = new ::QLabel("&Autor");
  ::QLineEdit *autor_field = new ::QLineEdit;
  Valid *autor_valid = new Valid(autor_field);
  autor_field->setValidator(autor_valid);
  autor->setBuddy(autor_field);
  ::QVBoxLayout *autor_layout = new ::QVBoxLayout;
  autor_layout->addWidget(autor);
  autor_layout->addWidget(autor_field);

  ::QHBoxLayout *book_layout = new ::QHBoxLayout;
  book_layout->addLayout(name_layout);
  book_layout->addLayout(autor_layout);

  ::QHBoxLayout *button_layout = new ::QHBoxLayout;
  for (const auto &j : comand_list_) {
    ::QPushButton *execute = new ::QPushButton(j);
    connect(execute, &QPushButton::clicked, [=]() {
      set_book(Book{name_field->text().toStdString(),
                       autor_field->text().toStdString()});
    });
    connect(execute, SIGNAL(clicked()), SLOT(for_books()));
    button_layout->addWidget(execute);
  }
  ::QVBoxLayout *general_layout = new ::QVBoxLayout;
  general_layout->addWidget(rezult);
  general_layout->addLayout(book_layout);
  general_layout->addLayout(button_layout);

  retval.second->setLayout(general_layout);

  return retval;
}

void Screen::for_books() {
  ::QString retval;
  auto comand = reinterpret_cast<::QPushButton *>(sender())->text();
  if (cur_book_.get_name().empty() && cur_book_.get_autor().empty()) {
    retval = "Input datas, please";
  } else {
    if (comand == comand_list_[0]) {
      if (cur_book_.get_name().empty()) {
        auto finded = library_.find_autor(cur_book_.get_autor());
        if (finded.empty()) {
          retval = "Library hasn't books of this autor";
        } else {
          retval = "Library has " + retval.setNum(finded.size()) +
                   " book(s) of this autor";
          if (finded.size() == 1) {
            set_book(finded.front()->first);
            emit book_in();
          }
        }
      } else {
        auto finded = library_.find_book(cur_book_);
        if (std::get<0>(finded) == std::get<1>(finded)) {
          retval = "Library hasn't this";
        } else {
          retval = "Library has " +
                   retval.setNum(std::distance(std::get<0>(finded),
                                               std::get<1>(finded))) +
                   " books with this name.";
          if (std::get<2>(finded)) {
            if (cur_book_.get_autor().empty()) {
              set_book(std::get<0>(finded)->first);
            }
            emit book_in();
          }
        }
      }
    } else if (comand == comand_list_[1]) {
      if (cur_book_.get_name().empty() || cur_book_.get_autor().empty()) {
        retval = "Input data, please";
      } else {
        library_.add_book(cur_book_.get_name(), cur_book_.get_autor());
        retval = "Executed";
        emit book_in();
      }
    } else if (comand == comand_list_[2]) {
      if (cur_book_.get_name().empty()) {
        retval = "Input data, please";
      } else {
        if (library_.remove_book(cur_book_)) {
          retval = "Executed";
        } else {
          retval = "Not removed";
        }
      }
    }
  }
  emit book_rezult(retval);
}

void Screen::for_readers() {
  ::QString retval;
  auto comand = reinterpret_cast<::QPushButton *>(sender())->text();
  if (cur_reader_.get_name().empty() || cur_reader_.get_surname().empty()) {
    retval = "Input data, please";
  } else {
    if (comand == comand_list_[0]) {
      auto finded = library_.find_reader(cur_reader_);
      if (finded.second) {
        retval = "The reader read " +
                 retval.setNum(finded.first->second.size()) + " books now";
        emit reader_in();
      } else {
        retval = "Library hasn't the reader";
      }
    } else if (comand == comand_list_[1]) {
      if (library_.register_reader(cur_reader_).second) {
        retval = "Executed";
      } else {
        retval = "Library already has the reader";
      }
      emit reader_in();
    } else if (comand == comand_list_[2]) {
      if (library_.erase_reader(cur_reader_)) {
        retval = "Executed";
      } else {
        retval = "Library hasn't the reader";
      }
    }
  }
  emit reader_rezult(retval);
}

void Screen::give_book() {
  try {
    library_.give_book_reader(cur_book_, cur_reader_);
    emit problem("Executed");
  } catch (std::invalid_argument &in) {
    emit problem(in.what());
  } catch (std::length_error &in) {
    emit problem(in.what());
  }
}

void Screen::take_book() {
  try {
    library_.take_book_reader(cur_book_, cur_reader_);
    emit problem("Executed");
  } catch (std::invalid_argument &in) {
    emit problem(in.what());
  }
}

void Screen::set_book(const Book &in) {
  cur_book_ = in;
}

void Screen::set_reader(const Reader &in) {
  cur_reader_ = in;
}
