// tst_check_available_groceries.cpp
#include <QString>
#include <QtTest>

#include "check_available_groceries.h"
#include "../../entities/grocery_items.h"
#include "../../repositories/grocery_items_repo_dummy.h"

class Usecases_check_available_groceries : public QObject
{
    Q_OBJECT

public:
    Usecases_check_available_groceries();

private Q_SLOTS:
    void test_one_or_more_grocery_items_available();
};

Usecases_check_available_groceries::Usecases_check_available_groceries()
{
}

void Usecases_check_available_groceries::test_one_or_more_grocery_items_available()
{
    // Given there is a list of available grocery items
    auto groceryItems = new entities::GroceryItems(this);
    QVERIFY(groceryItems);
    // And one or more grocery items are actually available
    auto groceryItemsRepoDummy = new repositories::GroceryItemsRepoDummy(groceryItems);
    groceryItems->setRepository(groceryItemsRepoDummy);
    QVERIFY(groceryItemsRepoDummy->count() > 0);
    // When I check available groceries
    auto checkAvailableGroceries = new usecases::CheckAvailableGroceries(groceryItems, this);
    QSignalSpy checkAvailableGroceriesSuccess(checkAvailableGroceries, &usecases::CheckAvailableGroceries::success);
    checkAvailableGroceries->run();
    QTRY_COMPARE_WITH_TIMEOUT(checkAvailableGroceriesSuccess.count(), 1, 1000);
    // Then I am given the list of available grocery items
    QCOMPARE(groceryItems->list().count(), groceryItemsRepoDummy->count());
    // And the grocery items are ordered by name, ascending
    QVERIFY(groceryItems->isSortedBy("name","ASC"));
}

QTEST_MAIN(Usecases_check_available_groceries)

#include "tst_check_available_groceries.moc"
