#include "broadcaster.h"

entities::Broadcaster::Broadcaster(QObject *parent) : QObject(parent)
{

}

QList<QVariantMap> entities::Broadcaster::lastPublishedReadings() const {
    return _lastPublishedReadings;
}

void entities::Broadcaster::publishReadings(QVariantMap sensorReading) {
    _lastPublishedReadings.clear();
    _lastPublishedReadings.append(sensorReading);
    emit readingsPublished(_lastPublishedReadings);
}
