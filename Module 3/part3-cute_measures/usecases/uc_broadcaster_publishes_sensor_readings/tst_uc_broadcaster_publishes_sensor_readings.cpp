#include <QString>
#include <QtTest>
#include "broadcaster_publishes_sensor_readings.h"

#include "../../entities/entity_broadcaster/broadcaster.h"
#include "../../entities/entity_sensor/sensor.h"
#include "../uc_broadcaster_connects_to_sensor/brodcaster_connects_to_sensor.h"

class Uc_broadcaster_publishes_sensor_readings : public QObject
{
    Q_OBJECT

public:
    Uc_broadcaster_publishes_sensor_readings();

private Q_SLOTS:
    void init();
    void cleanup();
    void test_sensor_emits_single();
    void test_sensor_emits_several();

private:
    entities::Broadcaster* _broadcaster;
    entities::Sensor* _sensor;
};



Uc_broadcaster_publishes_sensor_readings::Uc_broadcaster_publishes_sensor_readings()
{
}

void Uc_broadcaster_publishes_sensor_readings::init()
{
    // Given there is a broadcaster
    _broadcaster = new entities::Broadcaster;
    QVERIFY(_broadcaster);
    // And there is a sensor
    _sensor =  new entities::Sensor("mockSensor1");
    QVERIFY(_sensor);
    // And the broadcaster connects to the sensor
    QVERIFY(usecases::broadcaster_connects_to_sensor(*_broadcaster, *_sensor));
}

void Uc_broadcaster_publishes_sensor_readings::cleanup()
{
    delete _broadcaster; _broadcaster = nullptr;
    delete _sensor; _sensor = nullptr;
}

void Uc_broadcaster_publishes_sensor_readings::test_sensor_emits_single()
{
    // And the sensor emits a reading
    QSignalSpy sensorEmitReading(_sensor, SIGNAL(emitReading(QVariantMap)));
    _sensor->emitReading(QVariantMap({
                                         {"sensor_id", _sensor->identifier()},
                                         {"timestamp", QDateTime::currentMSecsSinceEpoch()},
                                         {"value", 1.5}
                                     }));
    QCOMPARE(sensorEmitReading.count(), 1);
    // When the broadcaster publishes the sensor readings
    bool published_reading_coincides_with_sensor_reading =
            usecases::broadcaster_publishes_sensor_readings(*_broadcaster, *_sensor);
    // Then the corresponding published reading coincides with the sensor reading
    QVERIFY(published_reading_coincides_with_sensor_reading);
}

void Uc_broadcaster_publishes_sensor_readings::test_sensor_emits_several()
{
    // And the sensor emits n readings
    int n = 5;
    QSignalSpy sensorEmitReading(_sensor, SIGNAL(emitReading(QVariantMap)));
    for(int i=0;i<n;i++) {
        QTest::qSleep(500);
        _sensor->emitReading(QVariantMap({
                                             {"sensor_id", _sensor->identifier()},
                                             {"timestamp", QDateTime::currentMSecsSinceEpoch()},
                                             {"value", 1.5*i}
                                         }));
        QCOMPARE(sensorEmitReading.count(), i+1);
        // When the broadcaster publishes the sensor readings
        bool published_reading_coincides_with_sensor_reading = usecases::broadcaster_publishes_sensor_readings(*_broadcaster, *_sensor);
        // Then the corresponding published reading coincides with the sensor reading
        QVERIFY(published_reading_coincides_with_sensor_reading);
    }
}

QTEST_MAIN(Uc_broadcaster_publishes_sensor_readings)

#include "tst_uc_broadcaster_publishes_sensor_readings.moc"
