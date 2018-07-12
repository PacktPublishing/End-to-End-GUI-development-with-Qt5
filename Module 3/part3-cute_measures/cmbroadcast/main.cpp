// cmbroadcast/main.cpp
#include <QCoreApplication>
#include <QTimer>
#include <QDateTime>
#include <QVariantMap>
#include <QtMath>
#include "../channels/channel_broadcaster/broadcaster_bt.h"
//#include "../channels/channel_broadcaster/broadcaster_http.h"
#include "../entities/entity_broadcaster/broadcaster.h"
#include "../entities/entity_sensor/sensor.h"
#include "../usecases/uc_broadcaster_connects_to_sensor/brodcaster_connects_to_sensor.h"
#include "../usecases/uc_broadcaster_publishes_sensor_readings/broadcaster_publishes_sensor_readings.h"

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    QTimer::singleShot(600000, &app, SLOT(quit()));

    auto broadcasterBt = new channels::BroadcasterBt(&app);
    //    auto broadcasterHttp = new channels::BroadcasterHttp(&app);
    auto broadcaster = new entities::Broadcaster(&app);

    if (broadcasterBt->init()) {
        broadcasterBt->connectToBroadcaster(broadcaster);
    }
    //    if (broadcasterHttp->init()) {
    //        broadcasterHttp->connectToBroadcaster(broadcaster);
    //    }

    auto sensor = new entities::Sensor("mockSensor1", &app);

    usecases::broadcaster_connects_to_sensor(*broadcaster, *sensor);
    sensor->emitReading(
                QVariantMap({
                                {"sensor_id", sensor->identifier()},
                                {"timestamp", QDateTime::currentMSecsSinceEpoch()},
                                {"value", 1.5}
                            }));

    qDebug() << (usecases::broadcaster_publishes_sensor_readings(*broadcaster, *sensor)
                 ? "readings published"
                 : "readings not published");
    QTimer sensorTimer;
    sensorTimer.setInterval(1000);
    QObject::connect(&sensorTimer, &QTimer::timeout, [&sensor] {
        sensor->emitReading(
                    QVariantMap({
                                    {"sensor_id", sensor->identifier()},
                                    {"timestamp", QDateTime::currentMSecsSinceEpoch()},
                                    {"value", qSin(QDateTime::currentMSecsSinceEpoch())}
                                }));
    });
    QObject::connect(broadcasterBt, &channels::BroadcasterBt::clientConnected, [&sensorTimer] {
        sensorTimer.start();
    });

    return app.exec();
}
