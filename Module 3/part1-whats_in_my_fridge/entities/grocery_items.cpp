// grocery_items.cpp
#include <algorithm>
#include <QVariant>
#include "grocery_items.h"
#include "../repositories/grocery_items_repo.h"

namespace entities {

GroceryItems::GroceryItems(QObject *parent)
    : QObject(parent),
      m_list(QVariantList()),
      m_repository(nullptr)
{}

GroceryItems::~GroceryItems()
{}

void GroceryItems::create(const QString& name)
{
    m_isSortedByNameAsc = false;
    m_list.append(QVariantMap{{"name", name}});
    sortBy("name","ASC");
    emit listChanged();
    emit created("ENTITIES_GROCERY_ITEMS__CREATED");
}

bool GroceryItems::contains(const QString &field, const QString &value) const
{
    return m_list.contains(QVariantMap{{field, value}});
}

void GroceryItems::sortBy(const QString &field, const QString &direction)
{
    if (field == "name" && direction == "ASC") {
        std::sort(m_list.begin(), m_list.end(), [](const QVariant &v1, const QVariant &v2) {
            return v1.toMap().value("name") < v2.toMap().value("name");
        });
        m_isSortedByNameAsc = true;
    }
}

bool GroceryItems::isSortedBy(const QString &field, const QString &direction) const {
    if (field == "name" && direction=="ASC") {
        return m_isSortedByNameAsc;
    } else {
        return false;
    }
}

void GroceryItems::setRepository(repositories::GroceryItemsRepo *repository)
{
    m_repository = repository;
    connect(m_repository, &repositories::GroceryItemsRepo::allRecordsRetrieved,
            this, &GroceryItems::onAllRecordsRetrieved,
            Qt::UniqueConnection);
}

void GroceryItems::retrieveAll()
{
    if (m_repository) {
        m_repository->retrieveAllRecords();
    }
}

QVariantList GroceryItems::list() const
{
    return m_list;
}

void GroceryItems::onAllRecordsRetrieved(const QVariantList& records)
{
    m_list = records;
    sortBy("name","ASC");
    emit listChanged();
    emit allRetrieved("ENTITIES_GROCERY_ITEMS__ALL_RETRIEVED");
}
}
