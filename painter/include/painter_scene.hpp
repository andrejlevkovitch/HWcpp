// painter_scene.hpp

#pragma once

#include <QGraphicsScene>

namespace painter {
class painter_scene : public ::QGraphicsScene {
  Q_OBJECT
public:
  enum figure {
    NONE,
    DEL,
    LINE,
    CURVED_LINE,
    SQUARE,
    CIRCLE,
    RECTANGLE,
    ELLIPS
  };

private:
  ::QPointF last_pos_;
  figure figure_;
  ::QGraphicsItem *cur_figure_;
  ::QPen pen_;

public:
  painter_scene(::QObject *parent = nullptr);
  ~painter_scene();
  void mousePressEvent(::QGraphicsSceneMouseEvent *event) override;
  void mouseReleaseEvent(::QGraphicsSceneMouseEvent *event) override;
  void mouseMoveEvent(::QGraphicsSceneMouseEvent *event) override;

public slots:
  void set_figure(figure);
  void open_file(const ::QString &name);
  void save_file(const ::QString &name);
  void set_pen_size(int size);
  void set_pen_color(::QColor color);
};
}; // namespace painter
