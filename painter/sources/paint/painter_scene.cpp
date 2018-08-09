// painter_scene.cpp

#include "painter_scene.hpp"
#include <QApplication>
#include <QGraphicsItem>
#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <QPainterPath>

painter::painter_scene::painter_scene(::QObject *parent)
    : QGraphicsScene{parent}, figure_{NONE},
      cur_figure_{nullptr}, pen_{Qt::black, 3} {}

painter::painter_scene::~painter_scene() {
  this->clear();
}

void painter::painter_scene::mousePressEvent(
    ::QGraphicsSceneMouseEvent *event) {
  last_pos_ = event->scenePos();
  switch (figure_) {
  case NONE: {
    if ((cur_figure_ = itemAt(last_pos_, ::QTransform{}))) {
      ::QApplication::setOverrideCursor(Qt::PointingHandCursor);
    }
  } break;
  case LINE: {
    ::QLine line{last_pos_.toPoint(), last_pos_.toPoint()};
    cur_figure_ = addLine(line, pen_);
    cur_figure_->setFlag(::QGraphicsItem::ItemIsMovable);
  } break;
  case CURVED_LINE: {
    ::QPainterPath pp{last_pos_};
    cur_figure_ = addPath(pp, pen_);
    static_cast<::QGraphicsPathItem *>(cur_figure_)->setPath(pp);
    cur_figure_->setFlags(::QGraphicsItem::ItemIsMovable);
  } break;
  case SQUARE: {
    ::QRect rect{last_pos_.toPoint(), ::QSize{}};
    cur_figure_ = addRect(rect, pen_);
    cur_figure_->setFlag(::QGraphicsItem::ItemIsMovable);
  } break;
  case CIRCLE: {
    ::QRect rect{last_pos_.toPoint(), ::QSize{}};
    cur_figure_ = addEllipse(rect, pen_);
    cur_figure_->setFlag(::QGraphicsItem::ItemIsMovable);
  } break;
  case RECTANGLE: {
    ::QRect rect{last_pos_.toPoint(), ::QSize{}};
    cur_figure_ = addRect(rect, pen_);
    cur_figure_->setFlag(::QGraphicsItem::ItemIsMovable);
  } break;
  case ELLIPS: {
    ::QRect rect{last_pos_.toPoint(), ::QSize{}};
    cur_figure_ = addEllipse(rect, pen_);
    cur_figure_->setFlag(::QGraphicsItem::ItemIsMovable);
  } break;
  default:
    break;
  }
}

void painter::painter_scene::mouseReleaseEvent(
    ::QGraphicsSceneMouseEvent *event) {
  ::QApplication::restoreOverrideCursor();
}

void painter::painter_scene::mouseMoveEvent(::QGraphicsSceneMouseEvent *event) {
  auto temp = event->scenePos();
  if (event->buttons() == Qt::MouseButton::LeftButton) {
    switch (figure_) {
    case NONE:
      if (cur_figure_) {
        cur_figure_->setPos(cur_figure_->scenePos() + (temp - last_pos_));
        last_pos_ = temp;
      }
      break;
    case LINE: {
      ::QLine line{last_pos_.toPoint(), event->scenePos().toPoint()};
      static_cast<::QGraphicsLineItem *>(cur_figure_)->setLine(line);
    } break;
    case CURVED_LINE: {
      auto path = static_cast<::QGraphicsPathItem *>(cur_figure_)->path();
      path.lineTo(temp);
      static_cast<::QGraphicsPathItem *>(cur_figure_)->setPath(path);
    } break;
    case SQUARE: {
      int hight = temp.y() - last_pos_.y();
      int width = temp.x() - last_pos_.x();
      if (std::abs(hight) > std::abs(width)) {
        hight = (hight > 0) ? std::abs(width) : -std::abs(width);
      } else {
        width = (width > 0) ? std::abs(hight) : -std::abs(hight);
      }
      ::QRect rect{last_pos_.toPoint(), ::QSize{width, hight}};
      static_cast<::QGraphicsRectItem *>(cur_figure_)
          ->setRect(rect.normalized());
    } break;
    case CIRCLE: {
      int hight = temp.y() - last_pos_.y();
      int width = temp.x() - last_pos_.x();
      if (std::abs(hight) > std::abs(width)) {
        hight = (hight > 0) ? std::abs(width) : -std::abs(width);
      } else {
        width = (width > 0) ? std::abs(hight) : -std::abs(hight);
      }
      ::QRect rect{last_pos_.toPoint(), ::QSize{width, hight}};
      static_cast<::QGraphicsEllipseItem *>(cur_figure_)
          ->setRect(rect.normalized());
    } break;
    case RECTANGLE: {
      int hight = temp.y() - last_pos_.y();
      int width = temp.x() - last_pos_.x();
      ::QRect rect{last_pos_.toPoint(), ::QSize{width, hight}};
      static_cast<::QGraphicsRectItem *>(cur_figure_)
          ->setRect(rect.normalized());
    } break;
    case ELLIPS: {
      int hight = temp.y() - last_pos_.y();
      int width = temp.x() - last_pos_.x();
      ::QRect rect{last_pos_.toPoint(), ::QSize{width, hight}};
      static_cast<::QGraphicsEllipseItem *>(cur_figure_)
          ->setRect(rect.normalized());
    } break;
    default:
      break;
    }
  }
}

void painter::painter_scene::set_figure(figure f) { figure_ = f; }

void painter::painter_scene::open_file(const ::QString &name) {
  if (!name.isEmpty()) {
    this->clear();
    ::QPixmap image{name};
    this->addPixmap(image);
  }
}

void painter::painter_scene::save_file(const ::QString &name) {
  if (!name.isEmpty()) {
    ::QImage image{::QSize(this->width(), this->height()),
                   ::QImage::Format_RGB16};
    image.fill(Qt::white);

    ::QPainter pn;
    pn.begin(&image);
    this->render(&pn);
    pn.end();
    image.save(name);
  }
}

void painter::painter_scene::set_pen_size(int size) { pen_.setWidth(size); }

void painter::painter_scene::set_pen_color(::QColor color) {
  if (color.isValid()) {
    pen_.setColor(color);
  }
}
