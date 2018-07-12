#include <QObject>

#include "../../entities/entity_sensor/sensor.h"
#include "../../entities/entity_broadcaster/broadcaster.h"

#include "brodcaster_connects_to_sensor.h"

bool usecases::broadcaster_connects_to_sensor(const entities::Broadcaster& broadcaster, const entities::Sensor& sensor) {
    return QObject::connect(
                &sensor, &entities::Sensor::emitReading,
                &broadcaster, &entities::Broadcaster::publishReadings,
                Qt::UniqueConnection);
}
