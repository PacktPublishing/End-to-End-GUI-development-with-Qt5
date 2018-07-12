// broadcaster_bt.cpp
#include <QDebug>
//#include <QBluetoothUuid>
#include <QBluetoothServer>
//#include <QBluetoothServiceDiscoveryAgent>
//#include <QBluetoothDeviceInfo>
#include <QBluetoothLocalDevice>
#include <QBluetoothServiceInfo>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>

#include "broadcaster_bt.h"

namespace channels {
static const QLatin1String serviceUuid("e8e10f95-1a70-4b27-9ccf-02010264e9c8");
}

channels::BroadcasterBt::BroadcasterBt(QObject* parent)
    : BroadcasterChannel(parent)
{
    qDebug() << Q_FUNC_INFO;
}

bool channels::BroadcasterBt::init() {
    qDebug() << Q_FUNC_INFO;
    if (!_listenToAdapter()) return false;
    if (!_provideServiceId()) return false;
    if (!_provideServiceTraits()) return false;
    if (!_provideServiceDiscoverability()) return false;
    if (!_provideProtocolDescriptorList()) return false;
    if (!_registerService()) return false;
    return true;
}

void channels::BroadcasterBt::sendReadings(QList<QVariantMap> readings)
{
    //    QByteArray message =
    //            readings.at(0).value("sensor_id").toByteArray()
    //            + "-" + readings.at(0).value("timestamp").toByteArray()
    //            + "-" + readings.at(0).value("value").toByteArray()
    //            +"\n";
    QJsonArray readingsJson;
    for (int i=0;i<readings.count();++i) {
        readingsJson.append(QJsonObject::fromVariantMap(readings.at(0)));
    }
    qDebug() << readingsJson;
    QByteArray message = QJsonDocument(readingsJson).toJson(QJsonDocument::Compact);
    if (_clientSocket) {
        _clientSocket->write(message);
        qDebug() << message;
    } else qDebug() << Q_FUNC_INFO << "no client socket!";
}

bool channels::BroadcasterBt::_listenToAdapter()
{
    qDebug() << Q_FUNC_INFO;
    _localAdapter = QBluetoothLocalDevice::allDevices().value(0).address();
    QBluetoothLocalDevice localDevice(_localAdapter);
    localDevice.setHostMode(QBluetoothLocalDevice::HostDiscoverable);
    _server = new QBluetoothServer(QBluetoothServiceInfo::RfcommProtocol, this);
    connect(_server, &QBluetoothServer::newConnection,
            this, &BroadcasterBt::_whenNewConnection);
    bool success = _server->listen(_localAdapter);
    qDebug() << (success ? "listening: " : "not listening: ")  << localDevice.name();
    return success;
}

bool channels::BroadcasterBt::_provideProtocolDescriptorList()
{
    qDebug() << Q_FUNC_INFO;
    QBluetoothServiceInfo::Sequence protocolDescriptorList;
    QBluetoothServiceInfo::Sequence protocol;
    protocol << QVariant::fromValue(QBluetoothUuid(QBluetoothUuid::L2cap));
    protocolDescriptorList.append(QVariant::fromValue(protocol));
    protocol.clear();
    protocol << QVariant::fromValue(QBluetoothUuid(QBluetoothUuid::Rfcomm))
             << QVariant::fromValue(quint8(_server->serverPort()));
    protocolDescriptorList.append(QVariant::fromValue(protocol));
    _serviceInfo.setAttribute(QBluetoothServiceInfo::ProtocolDescriptorList, protocolDescriptorList);
    return _serviceInfo.isComplete();
}

bool channels::BroadcasterBt::_provideServiceId()
{
    qDebug() << Q_FUNC_INFO;
    QBluetoothServiceInfo::Sequence classId;
    classId << QVariant::fromValue(QBluetoothUuid(QBluetoothUuid::SerialPort));
    _serviceInfo.setAttribute(QBluetoothServiceInfo::BluetoothProfileDescriptorList, classId);
    classId.prepend(QVariant::fromValue(QBluetoothUuid(serviceUuid)));
    _serviceInfo.setAttribute(QBluetoothServiceInfo::ServiceClassIds, classId);
    _serviceInfo.setServiceUuid(QBluetoothUuid(serviceUuid));
    return _serviceInfo.isValid();
}

bool channels::BroadcasterBt::_provideServiceDiscoverability()
{
    qDebug() << Q_FUNC_INFO;
    QBluetoothServiceInfo::Sequence publicBrowse;
    publicBrowse << QVariant::fromValue(QBluetoothUuid(QBluetoothUuid::PublicBrowseGroup));
    _serviceInfo.setAttribute(QBluetoothServiceInfo::BrowseGroupList, publicBrowse);
    return _serviceInfo.isValid();
}

bool channels::BroadcasterBt::_provideServiceTraits()
{
    qDebug() << Q_FUNC_INFO;
    _serviceInfo.setAttribute(QBluetoothServiceInfo::ServiceName, "CM BT Broadcaster Channel");
    _serviceInfo.setAttribute(QBluetoothServiceInfo::ServiceDescription, "Cute Measures bluetooth broadcaster channel for sensor readings");
    _serviceInfo.setAttribute(QBluetoothServiceInfo::ServiceProvider, "Cute Measures");
    return _serviceInfo.isValid();
}

bool channels::BroadcasterBt::_registerService()
{
    qDebug() << Q_FUNC_INFO;
    bool success = _serviceInfo.registerService(_localAdapter);
    if (success) qDebug()
            << "registered service" << _serviceInfo.serviceName()
            << "on adapter" << _localAdapter.toString();
    return success;
}

void channels::BroadcasterBt::_whenNewConnection()
{
    qDebug() << Q_FUNC_INFO;
    QBluetoothSocket *socket = _server->nextPendingConnection();
    connect(socket, &QBluetoothSocket::readyRead, [=] {
        qDebug() << socket->peerName();
    });
    if (!socket)
        return;
    _clientSocket = socket;
    qDebug() << _clientSocket->peerName();
    emit clientConnected(_clientSocket->peerName());
}
