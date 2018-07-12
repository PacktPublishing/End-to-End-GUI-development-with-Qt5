#include <QString>
#include <QtTest>

class Entities_GroceryItems : public QObject
{
    Q_OBJECT

public:
    Entities_GroceryItems();

private Q_SLOTS:
    void testCase1();
};

Entities_GroceryItems::Entities_GroceryItems()
{
}

void Entities_GroceryItems::testCase1()
{
    QVERIFY2(true, "Failure");
}

QTEST_APPLESS_MAIN(Entities_GroceryItems)

#include "tst_grocery_items.moc"
