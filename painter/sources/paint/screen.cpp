// screen.cpp

#include "screen.hpp"
#include "painter_scene.hpp"
#include "painter_view.hpp"
#include <QBoxLayout>
#include <QColorDialog>
#include <QFileDialog>
#include <QLabel>
#include <QMenuBar>
#include <QPushButton>
#include <QSpinBox>
#include <QStackedLayout>
#include <QStatusBar>
#include <QToolBar>

painter::screen::screen(::QWidget *parent) : ::QWidget{parent} {
  auto menu_bar = new ::QMenuBar;
  auto tool_bar_v = new ::QToolBar;
  tool_bar_v->setOrientation(Qt::Vertical);
  auto tool_bar_h = new ::QToolBar;
  tool_bar_h->setOrientation(Qt::Horizontal);
  auto stat_bar = new ::QStatusBar;

  auto scene = new painter::painter_scene{this};
  {
    scene->setSceneRect(0, 0, 500, 500);
    connect(this, SIGNAL(send_open_file(const ::QString &)), scene,
            SLOT(open_file(const ::QString &)));
    connect(this, SIGNAL(send_save_file(const ::QString &)), scene,
            SLOT(save_file(const ::QString &)));
  }
  auto view = new painter::painter_view;
  {
    view->setScene(scene);
    connect(view, &painter::painter_view::mouse_pos, stat_bar,
            [=](::QPoint pos) {
              stat_bar->clearMessage();
              stat_bar->showMessage(
                  ::QString{"x = %1, y = %2"}.arg(pos.x()).arg(pos.y()));
            });
  }

  auto color_layout = new ::QVBoxLayout;
  {
    color_layout->setSpacing(0);
    auto pen_color = new ::QPushButton;
    {
//    pen_color->setFlat(true);
      pen_color->setFixedSize(::QSize{40, 20});
      pen_color->setAutoFillBackground(true);
      pen_color->setPalette(::QPalette{::QPalette::Window, Qt::black});
      connect(pen_color, &::QPushButton::clicked, this, [=]() {
        auto color =
            ::QColorDialog::getColor(Qt::black, this, "choise pen color");
        if (color.isValid()) {
          scene->set_pen_color(color);
          pen_color->setPalette(::QPalette{::QPalette::Window, color});
        }
      });
    }
    auto brush_color = new ::QPushButton;
    {
      brush_color->setFixedSize(::QSize{40, 20});
      brush_color->setStyleSheet("background : white");
//    brush_color->setFlat(true);
      brush_color->setAutoFillBackground(true);
      brush_color->setPalette(::QPalette{::QPalette::Window, Qt::white});
      connect(brush_color, &::QPushButton::clicked, this, [=]() {
        auto color =
            ::QColorDialog::getColor(Qt::black, this, "choise brush color");
        if (color.isValid()) {
          scene->set_brush_color(color);
          brush_color->setPalette(::QPalette{::QPalette::Window, color});
        }
      });
    }

    color_layout->addWidget(pen_color);
    color_layout->addWidget(brush_color);
  }

  {
    auto file_menu = new ::QMenu{"File"};
    auto load_file = new ::QAction{"Load file"};
    connect(load_file, &::QAction::triggered, [=]() {
      emit send_open_file(
          ::QFileDialog::getOpenFileName(this, "Load", ".", "*.png"));
    });
    auto save_file = new ::QAction{"Save file"};
    connect(save_file, &::QAction::triggered, [=]() {
      emit send_save_file(
          ::QFileDialog::getSaveFileName(this, "Save", ".", "*.png"));
    });
    file_menu->addAction(load_file);
    file_menu->addAction(save_file);
    menu_bar->addMenu(file_menu);

    auto none = new ::QAction{"NONE", this};
    connect(none, &::QAction::triggered, scene,
            [=]() { scene->set_figure(painter_scene::NONE); });

    auto del = new ::QAction{"DEL", this};
    connect(del, &::QAction::triggered, scene,
            [=]() { scene->set_figure(painter_scene::DEL); });

    auto clear = new ::QAction{"CLEAR", this};
    connect(clear, &::QAction::triggered, scene,
            &painter::painter_scene::clear);

    auto line = new ::QAction{::QPixmap{":/line"}, "Line", this};
    connect(line, &::QAction::triggered, scene,
            [=]() { scene->set_figure(painter_scene::LINE); });

    auto curved_line =
        new ::QAction{::QPixmap{":/curved_line"}, "Curved line", this};
    connect(curved_line, &::QAction::triggered, scene,
            [=]() { scene->set_figure(painter_scene::CURVED_LINE); });

    auto square = new ::QAction{::QPixmap{":/square"}, "Square", this};
    connect(square, &::QAction::triggered, scene,
            [=]() { scene->set_figure(painter_scene::SQUARE); });

    auto circle = new ::QAction{::QPixmap{":/circle"}, "Circle", this};
    connect(circle, &::QAction::triggered, scene,
            [=]() { scene->set_figure(painter_scene::CIRCLE); });

    auto rectangle = new ::QAction{::QPixmap{":/rectangle"}, "Rectangle", this};
    connect(rectangle, &::QAction::triggered, scene,
            [=]() { scene->set_figure(painter_scene::RECTANGLE); });

    auto ellips = new ::QAction{::QPixmap{":/ellips"}, "Ellips", this};
    connect(ellips, &::QAction::triggered, scene,
            [=]() { scene->set_figure(painter_scene::ELLIPS); });

    auto counter = new ::QSpinBox{};
    counter->setButtonSymbols(::QSpinBox::UpDownArrows);
    connect(counter, SIGNAL(valueChanged(int)), scene, SLOT(set_pen_size(int)));
    counter->setRange(1, 30);

    tool_bar_v->addAction(line);
    tool_bar_v->addAction(curved_line);
    tool_bar_v->addAction(square);
    tool_bar_v->addAction(circle);
    tool_bar_v->addAction(rectangle);
    tool_bar_v->addAction(ellips);

    tool_bar_h->addAction(none);
    tool_bar_h->addAction(del);
    tool_bar_h->addAction(clear);
    tool_bar_h->addWidget(counter);
  }
  auto color_tool_layout = new ::QHBoxLayout;
  color_tool_layout->addLayout(color_layout);
  color_tool_layout->addWidget(tool_bar_h);

  auto dop_layout = new ::QHBoxLayout;
  dop_layout->addWidget(tool_bar_v);
  dop_layout->addWidget(view);

  auto general_layout = new ::QVBoxLayout;
  general_layout->addWidget(menu_bar);
  general_layout->addLayout(color_tool_layout);
  general_layout->addLayout(dop_layout);
  general_layout->addWidget(stat_bar);
  setLayout(general_layout);
}
