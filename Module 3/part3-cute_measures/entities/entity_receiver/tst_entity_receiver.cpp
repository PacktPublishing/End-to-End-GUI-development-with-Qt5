#include <QString>
#include <QtTest>

class Entity_receiver : public QObject
{
    Q_OBJECT

public:
    Entity_receiver();

private Q_SLOTS:
    void testCase1();
};

Entity_receiver::Entity_receiver()
{
}

void Entity_receiver::testCase1()
{
    QVERIFY2(true, "Failure");
}

QTEST_APPLESS_MAIN(Entity_receiver)

#include "tst_entity_receiver.moc"
