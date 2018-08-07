// painter_view.hpp

#pragma once

#include <QGraphicsView>

namespace painter {
class painter_view : public ::QGraphicsView {
  Q_OBJECT
private:
public:
  painter_view(::QWidget *parent = nullptr);
  void mouseMoveEvent(QMouseEvent *event) override;

signals:
  void mouse_pos(::QPoint);
};
}; // namespace painter
