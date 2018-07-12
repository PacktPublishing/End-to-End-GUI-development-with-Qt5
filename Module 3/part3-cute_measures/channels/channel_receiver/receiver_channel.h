#ifndef RECEIVER_CHANNEL_H
#define RECEIVER_CHANNEL_H

#include <QObject>
#include <QVariantList>

namespace entities {
class Receiver;
}

namespace channels {
class ReceiverChannel : public QObject
{
    Q_OBJECT
protected:
    ReceiverChannel(QObject *parent = nullptr) : QObject(parent) {}
public:
    virtual void init() = 0;
    bool connectToReceiver(entities::Receiver* receiver);
public slots:
    virtual void receiveReadings() = 0;
signals:
    void readingsProcessed(QVariantList readings);
};
}

#endif // RECEIVER_CHANNEL_H
