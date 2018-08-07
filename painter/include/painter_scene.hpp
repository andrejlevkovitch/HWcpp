// painter_scene.hpp

#pragma once

#include <QGraphicsScene>

namespace painter {
class painter_scene : public ::QGraphicsScene {
  Q_OBJECT
public:
  enum figure { NONE, LINE, CURVED_LINE, CIRCLE, RECTANGLE };

private:
  ::QPointF last_pos_;
  figure figure_;
  ::QGraphicsItem *cur_figure_;

public:
  painter_scene(::QObject *parent = nullptr);
  void mousePressEvent(::QGraphicsSceneMouseEvent *event) override;
  void mouseReleaseEvent(::QGraphicsSceneMouseEvent *event) override;
  void mouseMoveEvent(::QGraphicsSceneMouseEvent *event) override;

public slots:
  void set_figure(figure);
  void open_file(const ::QString &name);
  void save_file(const ::QString &name);
};
}; // namespace painter
