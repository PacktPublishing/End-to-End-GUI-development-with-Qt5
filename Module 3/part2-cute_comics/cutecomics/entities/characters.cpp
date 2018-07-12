#include "characters.h"

using namespace entities;

Characters::Characters(QObject *parent)
    : QAbstractListModel(parent)
{
}

int Characters::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return m_list.count();
}

QVariant Characters::data(const QModelIndex &index, int role) const
{
    if (! index.isValid())
        return QVariant();

    if (role == Qt::DisplayRole && index.column() == 0
            && index.row() < m_list.length())
        return m_list.at(index.row());
    return QVariant();
}

void Characters::add(const QString &name)
{
    if (! m_list.contains(name)) {
        beginInsertRows(QModelIndex(), m_list.count(), m_list.count());
        m_list.append(name);
        endInsertRows();
    }
}

void Characters::remove(const QString &name)
{
    int index = m_list.indexOf(name);
    if (index > -1) {
        beginRemoveRows(QModelIndex(), index, index);
        m_list.removeAt(index);
        endRemoveRows();
    }
}

//QVariant Characters::at(QModelIndex index)
//{
//    if (index.column() == 0)
//        return m_list.at(index.row());
//    return QVariant();
//}
