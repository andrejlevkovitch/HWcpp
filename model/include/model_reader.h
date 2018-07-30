// model_reader.h

#pragma once

#include "library.hpp"
#include <QAbstractItemModel>

class ModelReader : public ::QAbstractItemModel {
  Q_OBJECT
private:
  Journal journal_;

public:
  ModelReader(const Journal &journal, ::QObject *parent = nullptr);
  ::QVariant data(const ::QModelIndex &index, int Role) const;
  int rowCount(const ::QModelIndex &parent = ::QModelIndex{}) const;
  int columnCount(const ::QModelIndex &parent = ::QModelIndex{}) const;
  ::QVariant headerData(int nSection, Qt::Orientation,
                        int nRole = Qt::DisplayRole) const;
  Qt::ItemFlags flags(const ::QModelIndex &index) const;

  ::QModelIndex index(int row, int column,
                      const ::QModelIndex &parent = ::QModelIndex{}) const;
  ::QModelIndex parent(const ::QModelIndex &index) const;
};
