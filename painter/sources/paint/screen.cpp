// screen.cpp

#include "screen.hpp"
#include "painter_scene.hpp"
#include "painter_view.hpp"
#include <QBoxLayout>
#include <QFileDialog>
#include <QMenuBar>
#include <QStatusBar>
#include <QToolBar>

painter::screen::screen(::QWidget *parent) : ::QWidget{parent} {
  auto menu_bar = new ::QMenuBar;
  auto tool_bar = new ::QToolBar;
  auto stat_bar = new ::QStatusBar;

  auto scene = new painter::painter_scene;
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
    connect(load_file, &::QAction::triggered, this, [=]() {
      emit send_open_file(
          ::QFileDialog::getOpenFileName(this, "Load", ".", "*.png"));
    });
    auto save_file = new ::QAction{"Save file"};
    connect(save_file, &::QAction::triggered, this, [=]() {
      emit send_save_file(
          ::QFileDialog::getSaveFileName(this, "Save", ".", "*.png"));
    });
    file_menu->addAction(load_file);
    file_menu->addAction(save_file);
    menu_bar->addMenu(file_menu);
    auto none = new ::QAction{"NONE"};
    connect(none, &::QAction::triggered, scene,
            [=]() { scene->set_figure(painter_scene::NONE); });
    auto clear = new ::QAction{"CLEAR"};
    connect(clear, &::QAction::triggered, scene,
            &painter::painter_scene::clear);
    auto line = new ::QAction{::QPixmap{":/line"}, "Line"};
    connect(line, &::QAction::triggered, scene,
            [=]() { scene->set_figure(painter_scene::LINE); });
    auto curved_line = new ::QAction{::QPixmap{":/curved_line"}, "Curved line"};
    connect(curved_line, &::QAction::triggered, scene,
            [=]() { scene->set_figure(painter_scene::CURVED_LINE); });
    auto circle = new ::QAction{::QPixmap{":/circle"}, "Circle"};
    connect(circle, &::QAction::triggered, scene,
            [=]() { scene->set_figure(painter_scene::CIRCLE); });
    auto rectangle = new ::QAction{::QPixmap{":/rectangle"}, "Rectangle"};
    connect(rectangle, &::QAction::triggered, scene,
            [=]() { scene->set_figure(painter_scene::RECTANGLE); });
    tool_bar->addAction(none);
    tool_bar->addAction(clear);
    tool_bar->addAction(line);
    tool_bar->addAction(curved_line);
    tool_bar->addAction(circle);
    tool_bar->addAction(rectangle);
  }

  auto general_layout = new ::QVBoxLayout;
  general_layout->addWidget(menu_bar);
  general_layout->addWidget(tool_bar);
  general_layout->addWidget(view);
  general_layout->addWidget(stat_bar);
  setLayout(general_layout);
}
