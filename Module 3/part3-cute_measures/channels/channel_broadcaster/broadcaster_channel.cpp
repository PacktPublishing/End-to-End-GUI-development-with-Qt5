#include <QDebug>
#include "broadcaster_channel.h"
#include "../../entities/entity_broadcaster/broadcaster.h"

bool channels::BroadcasterChannel::connectToBroadcaster(entities::Broadcaster* broadcaster)
{
    qDebug() << Q_FUNC_INFO;
    return connect(broadcaster,&entities::Broadcaster::readingsPublished,
            this, &channels::BroadcasterChannel::sendReadings);
}
