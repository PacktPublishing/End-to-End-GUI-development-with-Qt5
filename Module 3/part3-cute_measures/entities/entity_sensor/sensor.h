#ifndef SENSOR_H
#define SENSOR_H

#include <QObject>
#include <QString>
#include <QVariantMap>

namespace entities {
class Sensor : public QObject
{
    Q_OBJECT
public:
    explicit Sensor(const QString& identifier, QObject *parent = nullptr);
    QVariantMap lastReading() const;
    QString identifier() const;
signals:
    void emitReading(QVariantMap sensorReading);
private slots:
    void _onEmitReading(QVariantMap sensorReading);
private:
    QVariantMap _lastReading;
    QString _identifier;
};
}

#endif // SENSOR_H
