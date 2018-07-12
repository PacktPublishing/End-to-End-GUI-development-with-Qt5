// add_grocery_item.h
#ifndef ADD_GROCERY_ITEM_H
#define ADD_GROCERY_ITEM_H

#include <QObject>

namespace entities {
    class GroceryItems;
}

namespace usecases {
class AddGroceryItem : public QObject
{
    Q_OBJECT
public:
    explicit AddGroceryItem(entities::GroceryItems* m_groceryItems, QObject *parent = nullptr);
    Q_INVOKABLE void run(const QString& type);

signals:
    void failure(QString message);
    void success(QString message);

private slots:
    void onGroceryItemCreated();
    void onGroceryItemNotCreated();

private:
    entities::GroceryItems* m_groceryItems;
};
}

#endif // ADD_GROCERY_ITEM_H
