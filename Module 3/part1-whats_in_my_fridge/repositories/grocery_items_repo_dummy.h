// grocery_items_repo_dummy.h
#ifndef GROCERY_ITEMS_REPO_DUMMY_H
#define GROCERY_ITEMS_REPO_DUMMY_H

#include <QObject>
#include <QVariantList>
#include "grocery_items_repo.h"

namespace repositories {

class GroceryItemsRepoDummy : public GroceryItemsRepo
{
    Q_OBJECT
public:
    explicit GroceryItemsRepoDummy(QObject *parent = nullptr)
        :GroceryItemsRepo(parent){}
    int count() const { return 3; }
    void retrieveAllRecords() {
        QVariantList recordsArray;
        recordsArray.push_back(QVariantMap{{"name", "bananas"}});
        recordsArray.push_back(QVariantMap{{"name", "apples"}});
        recordsArray.push_back(QVariantMap{{"name", "cheese"}});
        emit allRecordsRetrieved(recordsArray);
    }
};

}

#endif // GROCERY_ITEMS_REPO_DUMMY_H
