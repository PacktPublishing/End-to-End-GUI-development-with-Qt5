//#include <QDebug>
#include "sensor.h"

#include <QDateTime>

entities::Sensor::Sensor(const QString& identifier, QObject *parent) : QObject(parent)
{
    _identifier = identifier;
    connect(this,&Sensor::emitReading,
            this,&Sensor::_onEmitReading);
}

QVariantMap entities::Sensor::lastReading() const {
    return _lastReading;
}

QString entities::Sensor::identifier() const
{
    return _identifier;
}

void entities::Sensor::_onEmitReading(QVariantMap sensorReading)
{
    QDateTime timestamp;
    timestamp.setMSecsSinceEpoch(sensorReading.value("timestamp").toUInt());
    if (timestamp.isValid()) {
        _lastReading = sensorReading;
    }
}
