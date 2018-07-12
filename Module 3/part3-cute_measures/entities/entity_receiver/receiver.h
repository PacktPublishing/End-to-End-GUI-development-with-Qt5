#ifndef RECEIVER_H
#define RECEIVER_H

#include <QObject>
#include <QVariantList>

namespace entities {
class Receiver : public QObject
{
    Q_OBJECT
public:
    explicit Receiver(QObject *parent = nullptr);

signals:
    void readingsReceived(QVariantList readings);
};
}

#endif // RECEIVER_H
