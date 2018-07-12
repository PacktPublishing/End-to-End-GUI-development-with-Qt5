#ifndef CHARACTERS_H
#define CHARACTERS_H

#include <QAbstractListModel>

namespace entities {
class Characters : public QAbstractListModel
{
    Q_OBJECT

public:
    explicit Characters(QObject *parent = nullptr);

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    void add(const QString& name);
    void remove(const QString& name);
    //QVariant at(QModelIndex index);

private:
    QStringList m_list;
};
}

#endif // CHARACTERS_H
