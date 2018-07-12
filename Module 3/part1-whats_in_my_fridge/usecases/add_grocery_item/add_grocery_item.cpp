#include "add_grocery_item.h"
#include "../../entities/grocery_items.h"

namespace usecases {

AddGroceryItem::AddGroceryItem(entities::GroceryItems *groceryItems, QObject *parent)
    : QObject(parent),
      m_groceryItems(groceryItems)
{
    connect(m_groceryItems, &entities::GroceryItems::created,
            this, &AddGroceryItem::onGroceryItemCreated);
    connect(m_groceryItems ,&entities::GroceryItems::notCreated,
            this, &AddGroceryItem::onGroceryItemNotCreated);
}

void AddGroceryItem::run(const QString& name)
{
    m_groceryItems->create(name);
}

void AddGroceryItem::onGroceryItemCreated() {
    emit success("ADD_GROCERY_ITEM__SUCCESS");
}

void AddGroceryItem::onGroceryItemNotCreated() {
    emit failure("ADD_GROCERY_ITEM__FAILURE");
}

}
