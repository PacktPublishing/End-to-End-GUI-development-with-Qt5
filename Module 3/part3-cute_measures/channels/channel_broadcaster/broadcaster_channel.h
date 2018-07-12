#ifndef BROADCASTER_CHANNEL_H
#define BROADCASTER_CHANNEL_H

#include <QObject>
#include <QList>
#include <QVariantMap>

namespace entities {
class Broadcaster;
}

namespace channels {
class BroadcasterChannel : public QObject
{
    Q_OBJECT
protected:
    BroadcasterChannel(QObject *parent = nullptr) : QObject(parent) {}
public:
    virtual bool init() = 0;
    bool connectToBroadcaster(entities::Broadcaster* broadcaster);
public slots:
    virtual void sendReadings(QList<QVariantMap> readings) = 0;
};
}

#endif // BROADCASTER_CHANNEL_H
