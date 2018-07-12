#include <QDebug>
#include <QBluetoothSocket>
#include <QBluetoothServiceInfo>
#include <QBluetoothServiceDiscoveryAgent>
#include <QBluetoothLocalDevice>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>

#include "receiver_bt.h"

static const QLatin1String serviceUuid("e8e10f95-1a70-4b27-9ccf-02010264e9c8");

channels::ReceiverBt::ReceiverBt(QObject* parent)
    : ReceiverChannel(parent)
{
    qDebug() << Q_FUNC_INFO;
}

channels::ReceiverBt::~ReceiverBt()
{
    qDebug() << Q_FUNC_INFO;
}

void channels::ReceiverBt::receiveReadings()
{
    qDebug() << Q_FUNC_INFO;
    if (!_socket)
        return;
    QByteArray readingsLine = _socket->readLine();
    qDebug() << readingsLine;
    QJsonDocument readingsDoc = QJsonDocument::fromJson(readingsLine);
    QJsonArray readingsArray = readingsDoc.array();
    QVariantList readings;
    for (int i=0; i<readingsArray.count(); ++i) {
        readings.append(readingsArray.at(i).toObject().toVariantMap());
    }
    qDebug() << readings;
    emit readingsProcessed(readings);
}

void channels::ReceiverBt::init()
{
    qDebug() << Q_FUNC_INFO;
    auto localAdapter = QBluetoothLocalDevice::allDevices().at(0).address();
    _discoveryAgent = new QBluetoothServiceDiscoveryAgent(localAdapter, this);
    connect(_discoveryAgent, &QBluetoothServiceDiscoveryAgent::serviceDiscovered,
            this, &channels::ReceiverBt::_connectService);
    _discoveryAgent->setUuidFilter(QBluetoothUuid(serviceUuid));
    _discoveryAgent->start(QBluetoothServiceDiscoveryAgent::FullDiscovery);
}

void channels::ReceiverBt::_connectService(const QBluetoothServiceInfo &serviceInfo)
{
    qDebug() << Q_FUNC_INFO;
    _discoveryAgent->stop();
    qDebug() << "connecting to service" << serviceInfo.serviceName();
    _socket = new QBluetoothSocket(QBluetoothServiceInfo::RfcommProtocol, this);
    connect(_socket, &QBluetoothSocket::readyRead, this, &ReceiverBt::receiveReadings);
    connect(_socket, &QBluetoothSocket::connected, []{
        qDebug() << "socket connected";
    });
    _socket->connectToService(serviceInfo, QIODevice::ReadOnly);
}
