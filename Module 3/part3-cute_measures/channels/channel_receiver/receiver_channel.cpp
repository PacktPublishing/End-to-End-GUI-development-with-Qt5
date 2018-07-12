#include <QDebug>
#include "receiver_channel.h"
#include "../../entities/entity_receiver/receiver.h"



bool channels::ReceiverChannel::connectToReceiver(entities::Receiver* receiver)
{
    qDebug() << Q_FUNC_INFO;
    return connect(this, &channels::ReceiverChannel::readingsProcessed,
                   receiver, &entities::Receiver::readingsReceived);
}

