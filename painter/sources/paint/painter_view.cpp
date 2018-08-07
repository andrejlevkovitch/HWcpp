// painter_view.cpp

#include "painter_view.hpp"
#include <QMouseEvent>

painter::painter_view::painter_view(::QWidget *parent)
    : ::QGraphicsView{parent} {
  this->setMouseTracking(true);
  this->setRenderHint(::QPainter::Antialiasing, true);
}

void painter::painter_view::mouseMoveEvent(::QMouseEvent *event) {
  emit mouse_pos(event->pos());
  QGraphicsView::mouseMoveEvent(event);
}
