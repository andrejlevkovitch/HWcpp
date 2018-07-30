// model.h

#pragma once

#include "library.hpp"

#include <QAbstractListModel>
#include <QWidget>

class Model : public ::QAbstractListModel {
  Q_OBJECT
private:
  Bookcase *bookcase_;

public:
  Model(Bookcase *, ::QObject * = nullptr);
  ::QVariant data(const ::QModelIndex &index, int Role) const;
  int rowCount(const ::QModelIndex &parent = ::QModelIndex{}) const;
  int columnCount(const ::QModelIndex &parent = ::QModelIndex{}) const;
  ::QVariant headerData(int nSection, Qt::Orientation,
                      int nRole = Qt::DisplayRole) const;
  Qt::ItemFlags flags(const ::QModelIndex &index) const;
};
