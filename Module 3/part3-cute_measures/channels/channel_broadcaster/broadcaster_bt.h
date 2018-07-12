#ifndef BROADCASTER_BT_H
#define BROADCASTER_BT_H

#include <QBluetoothServer>

#include "broadcaster_channel.h"

namespace channels {
class BroadcasterBt : public BroadcasterChannel
{
    Q_OBJECT
public:
    explicit BroadcasterBt(QObject* parent = nullptr);
    bool init() override;
public slots:
    void sendReadings(QList<QVariantMap> readings) override;
signals:
    void clientConnected(const QString& clientName);

private slots:
    void _whenNewConnection();
private:
    QBluetoothServer* _server;
    QBluetoothAddress _localAdapter;
    QBluetoothServiceInfo _serviceInfo;
    QBluetoothSocket* _clientSocket;
    bool _listenToAdapter();
    bool _provideProtocolDescriptorList();
    bool _provideServiceId();
    bool _provideServiceDiscoverability();
    bool _provideServiceTraits();
    bool _registerService();
};
}

#endif // BROADCASTER_BT_H
