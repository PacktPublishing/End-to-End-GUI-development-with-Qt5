#ifndef BRODCASTER_CONNECTS_TO_SENSOR_H
#define BRODCASTER_CONNECTS_TO_SENSOR_H

namespace entities {
class Broadcaster;
class Sensor;
}

namespace usecases {
bool broadcaster_connects_to_sensor(const entities::Broadcaster& broadcaster, const entities::Sensor& sensor);
}

#endif // BRODCASTER_CONNECTS_TO_SENSOR_H
