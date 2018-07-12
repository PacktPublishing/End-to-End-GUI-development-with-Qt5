#include <QString>
#include <QtTest>

class Entity_sensor : public QObject
{
    Q_OBJECT

public:
    Entity_sensor();

private Q_SLOTS:
    void testCase1();
};

Entity_sensor::Entity_sensor()
{
}

void Entity_sensor::testCase1()
{
    QVERIFY2(true, "Failure");
}

QTEST_APPLESS_MAIN(Entity_sensor)

#include "tst_entity_sensor.moc"
