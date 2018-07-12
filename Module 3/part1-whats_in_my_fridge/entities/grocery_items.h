#ifndef GROCERY_ITEMS_H
#define GROCERY_ITEMS_H

#include <QObject>
#include <QVariantList>

namespace repositories {
class GroceryItemsRepo;
}

namespace entities {

class GroceryItems : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QVariantList list READ list NOTIFY listChanged)

public:
    explicit GroceryItems(QObject *parent = nullptr);
    ~GroceryItems();
    bool isSortedBy(const QString& field, const QString& direction) const;
    void create(const QString& type);
    bool contains(const QString& type, const QString& value) const;
    void sortBy(const QString& field, const QString& direction);
    QVariantList list() const;
    void retrieveAll();
    void setRepository(repositories::GroceryItemsRepo* repository);

signals:
    void allRetrieved(QString message);
    void allNotRetrieved(QString message);
    void created(QString message);
    void notCreated(QString message);
    void listChanged();

private:
    bool m_isSortedByNameAsc;
    QVariantList m_list;
    repositories::GroceryItemsRepo* m_repository;

private slots:
    void onAllRecordsRetrieved(const QVariantList& records);
    void onAllRecordsNotRetrieved(QString message) {}
};

}

#endif // GROCERY_ITEMS_H
