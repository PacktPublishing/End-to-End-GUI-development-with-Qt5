// grocery_items_repo.h
#ifndef GROCERY_ITEMS_REPO_H
#define GROCERY_ITEMS_REPO_H

#include <QObject>
#include <QVariantList>

namespace repositories {

class GroceryItemsRepo : public QObject
{
    Q_OBJECT
protected:
    explicit GroceryItemsRepo(QObject *parent = nullptr) : QObject(parent) {}
public:
    virtual int count() const = 0;
    virtual void retrieveAllRecords() = 0;

signals:
    void allRecordsRetrieved(QVariantList records);
};

}

#endif // GROCERY_ITEMS_REPO_H
