// screen.cpp

#include "screen.hpp"
#include "painter_scene.hpp"
#include "painter_view.hpp"
#include <QBoxLayout>
#include <QColorDialog>
#include <QFileDialog>
#include <QLabel>
#include <QMenuBar>
#include <QSpinBox>
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
  scene->setSceneRect(0, 0, 500, 500);
  connect(this, SIGNAL(send_open_file(const ::QString &)), scene,
          SLOT(open_file(const ::QString &)));
  connect(this, SIGNAL(send_save_file(const ::QString &)), scene,
          SLOT(save_file(const ::QString &)));
  auto view = new painter::painter_view;
  view->setScene(scene);
  connect(view, &painter::painter_view::mouse_pos, stat_bar, [=](::QPoint pos) {
    stat_bar->clearMessage();
    stat_bar->showMessage(
        ::QString{"x = %1, y = %2"}.arg(pos.x()).arg(pos.y()));
  });

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

    auto cur_color = new ::QLabel{};
    cur_color->setFixedWidth(20);
    cur_color->setPalette(::QPalette{::QPalette::Window, Qt::black});
    cur_color->setAutoFillBackground(true);

    auto set_color = new ::QAction{::QPixmap{":/color"}, "Set color", this};
    connect(set_color, &::QAction::triggered, this, [=]() {
      auto color =
          ::QColorDialog::getColor(Qt::black, this, "choise some color");
      if (color.isValid()) {
        scene->set_pen_color(color);
        cur_color->setPalette(::QPalette{::QPalette::Window, color});
      }
    });

    tool_bar_v->addAction(line);
    tool_bar_v->addAction(curved_line);
    tool_bar_v->addAction(square);
    tool_bar_v->addAction(circle);
    tool_bar_v->addAction(rectangle);
    tool_bar_v->addAction(ellips);
    tool_bar_h->addAction(none);
    tool_bar_h->addAction(clear);
    tool_bar_h->addWidget(counter);
    tool_bar_h->addWidget(cur_color);
    tool_bar_h->addAction(set_color);
  }
  auto dop_layout = new ::QHBoxLayout;
  dop_layout->addWidget(tool_bar_v);
  dop_layout->addWidget(view);

  auto general_layout = new ::QVBoxLayout;
  general_layout->addWidget(menu_bar);
  general_layout->addWidget(tool_bar_h);
  general_layout->addLayout(dop_layout);
  general_layout->addWidget(stat_bar);
  setLayout(general_layout);
}
