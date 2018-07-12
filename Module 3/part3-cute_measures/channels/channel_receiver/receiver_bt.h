#ifndef RECEIVER_BT_H
#define RECEIVER_BT_H

#include <QObject>

#include "receiver_channel.h"

class QBluetoothSocket;
class QBluetoothServiceInfo;
class QBluetoothServiceDiscoveryAgent;

namespace channels {
class ReceiverBt : public ReceiverChannel
{
    Q_OBJECT
public:
    explicit ReceiverBt(QObject* parent = nullptr);
    ~ReceiverBt();
    Q_INVOKABLE void init() override;
public slots:
    void receiveReadings() override;

private slots:
    void _connectService(const QBluetoothServiceInfo &serviceInfo);
private:
    QBluetoothSocket* _socket;
    QBluetoothServiceDiscoveryAgent* _discoveryAgent;
};
}

#endif // RECEIVER_BT_H
