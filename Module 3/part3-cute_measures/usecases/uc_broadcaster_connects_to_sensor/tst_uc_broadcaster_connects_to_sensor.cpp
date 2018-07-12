#include <QString>
#include <QtTest>

class Uc_broadcaster_connects_to_sensor : public QObject
{
    Q_OBJECT

public:
    Uc_broadcaster_connects_to_sensor();

private Q_SLOTS:
    void test_success();
};

Uc_broadcaster_connects_to_sensor::Uc_broadcaster_connects_to_sensor()
{
}

void Uc_broadcaster_connects_to_sensor::test_success()
{
    QVERIFY2(true, "Failure");
}

QTEST_APPLESS_MAIN(Uc_broadcaster_connects_to_sensor)

#include "tst_uc_broadcaster_connects_to_sensor.moc"
