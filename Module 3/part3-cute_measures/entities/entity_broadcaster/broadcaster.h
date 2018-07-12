#ifndef BROADCASTER_H
#define BROADCASTER_H

#include <QObject>
#include <QList>
#include <QVariantMap>

namespace entities {
class Broadcaster : public QObject
{
    Q_OBJECT
public:
    explicit Broadcaster(QObject *parent = nullptr);
    QList<QVariantMap> lastPublishedReadings() const;
signals:
    void readingsPublished(QList<QVariantMap> readings);
public slots:
    void publishReadings(QVariantMap sensorReading);

private:
    QList<QVariantMap> _lastPublishedReadings;
};
}

#endif // BROADCASTER_H
