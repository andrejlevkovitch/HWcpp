// model.cpp

#include "model.h"

Model::Model(Bookcase *bookcase, ::QObject *obj)
    : ::QAbstractListModel{obj}, bookcase_{bookcase} {}

::QVariant Model::data(const ::QModelIndex &index, int Role) const {
  if (!index.isValid() || index.row() < 0 || index.row() >= bookcase_->size() ||
      index.column() < 0 || index.column() >= 3) {
    return ::QVariant{};
  }
  auto iter = bookcase_->begin();
  std::advance(iter, index.row());
  if (Role == Qt::DisplayRole) {
    switch (index.column()) {
    case 0:
      return ::QString{iter->first.get_name().c_str()};
    case 1:
      return ::QString{iter->first.get_autor().c_str()};
    case 2:
      return ::QString::number(iter->second);
    default:
      break;
    }
  }
  return ::QVariant{};
}

int Model::rowCount(const ::QModelIndex &parent) const {
  if (parent.isValid()) {
    return 0;
  }
  return bookcase_->size();
}

int Model::columnCount(const ::QModelIndex &parent) const {
  if (parent.isValid()) {
    return 0;
  }
  return 3;
}

::QVariant Model::headerData(int nSection, Qt::Orientation orientation,
                             int nRole) const {
  if (nRole != Qt::DisplayRole) {
    return ::QVariant{};
  }
  if (orientation == Qt::Horizontal) {
    switch (nSection) {
    case 0:
      return ::QString{"Name"};
    case 1:
      return ::QString{"Autor"};
    case 2:
      return ::QString{"Capacity"};
    default:
      return ::QVariant{};
    }
  } else {
    return ::QString::number(nSection);
  }
}

Qt::ItemFlags Model::flags(const ::QModelIndex &index) const {
  Qt::ItemFlags flags = ::QAbstractItemModel::flags(index);
  return index.isValid() ? (flags | Qt::ItemIsEnabled) : flags;
}
