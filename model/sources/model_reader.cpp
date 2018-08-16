// model_reader.cpp

#include "model_reader.h"

ModelReader::ModelReader(const Journal &journal, ::QObject *parent)
    : ::QAbstractItemModel{parent}, journal_{journal} {}

::QVariant ModelReader::data(const ::QModelIndex &index, int Role) const {
  if (!index.isValid() || index.row() < 0 || index.row() >= journal_.size() ||
      index.column() < 0 || index.column() >= 3) {
    return ::QVariant{};
  }
  if (index.parent().isValid()) {
    auto iter = journal_.begin();
    std::advance(iter, index.parent().row());
    auto temp_iter = iter->second.begin();
    std::advance(iter, index.row());
    if (Role == Qt::DisplayRole) {
      switch (index.column()) {
      case 0:
        return ::QString{temp_iter->get_name().c_str()};
      case 1:
        return ::QString{temp_iter->get_autor().c_str()};
      default:
        break;
      }
    }
    return ::QVariant{};
  }
  auto iter = journal_.begin();
  std::advance(iter, index.row());
  if (Role == Qt::DisplayRole) {
    switch (index.column()) {
    case 0:
      return ::QString{iter->first.get_name().c_str()};
    case 1:
      return ::QString{iter->first.get_surname().c_str()};
    case 2:
      return ::QString::number(iter->second.size());
    case 3:
    default:
      break;
    }
  }
  return ::QVariant{};
}

int ModelReader::rowCount(const ::QModelIndex &parent) const {
  if (parent.isValid()) {
    return 0;
    auto iter = journal_.begin();
    std::advance(iter, parent.row());
    return iter->second.size();
  }
  return journal_.size();
}

int ModelReader::columnCount(const ::QModelIndex &parent) const {
  if (parent.isValid()) {
    return 0;
  }
  return 3;
}

::QVariant ModelReader::headerData(int nSection, Qt::Orientation orientation,
                                   int Role) const {
  if (Role != Qt::DisplayRole) {
    return ::QVariant{};
  }
  if (orientation == Qt::Horizontal) {
    switch (nSection) {
    case 0:
      return ::QString{"Name"};
    case 1:
      return ::QString{"Surname"};
    case 2:
      return ::QString{"Capasity"};
    default:
      return ::QVariant{};
    }
  } else {
    return ::QString::number(nSection);
  }
}

Qt::ItemFlags ModelReader::flags(const ::QModelIndex &index) const {
  Qt::ItemFlags flags = ::QAbstractItemModel::flags(index);
  return index.isValid() ? (flags | Qt::ItemIsEnabled) : flags;
}

::QModelIndex ModelReader::index(int row, int column,
                                 const ::QModelIndex &parent) const {
  if (!hasIndex(row, column, parent)) {
    return ::QModelIndex{};
  }
  if (!parent.isValid()) {
    auto iter = journal_.begin();
    std::advance(iter, row);
    const void *alfa = reinterpret_cast<const void *>(&(*iter));
    return createIndex(row, column, const_cast<void *>(alfa));
  } else {
    auto iter = reinterpret_cast<std::pair<Reader, std::list<Book>> *>(parent.internalPointer())->second.begin();
    std::advance(iter, row);
    return createIndex(row, column, parent.internalPointer());
  }
}

::QModelIndex ModelReader::parent(const ::QModelIndex &index) const {
  if (!index.isValid()) {
    return ::QModelIndex{};
  }
}
