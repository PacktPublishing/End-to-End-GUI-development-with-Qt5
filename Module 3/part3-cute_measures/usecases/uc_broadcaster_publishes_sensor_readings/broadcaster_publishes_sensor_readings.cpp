// broadcaster_publishes_sensor_reading.cpp
//#include <QDebug>
#include <QtGlobal>

#include "../../entities/entity_broadcaster/broadcaster.h"
#include "../../entities/entity_sensor/sensor.h"

#include "broadcaster_publishes_sensor_readings.h"

bool usecases::broadcaster_publishes_sensor_readings(entities::Broadcaster& broadcaster, entities::Sensor& sensor) {
//   qDebug() << Q_FUNC_INFO;
   quint64 broadcasterTimestamp = broadcaster.lastPublishedReadings().at(0).value("timestamp").toUInt();
   quint64 sensorTimeStamp = sensor.lastReading().value("timestamp").toUInt();
//   qDebug() << broadcasterTimestamp << sensorTimeStamp;
   return  broadcasterTimestamp > 0
           && sensorTimeStamp > 0
           && broadcasterTimestamp == sensorTimeStamp;
}
