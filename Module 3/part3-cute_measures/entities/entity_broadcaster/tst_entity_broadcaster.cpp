#include <QString>
#include <QtTest>

class Entity_broadcaster : public QObject
{
    Q_OBJECT

public:
    Entity_broadcaster();

private Q_SLOTS:
    void testCase1();
};

Entity_broadcaster::Entity_broadcaster()
{
}

void Entity_broadcaster::testCase1()
{
    QVERIFY2(true, "Failure");
}

QTEST_APPLESS_MAIN(Entity_broadcaster)

#include "tst_entity_broadcaster.moc"
