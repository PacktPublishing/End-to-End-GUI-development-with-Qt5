// broadcaster_http.cpp
#include "broadcaster_http.h"

#include <QHostAddress>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>

#include "qhttpserver.hpp"
#include "qhttpserverconnection.hpp"
#include "qhttpserverrequest.hpp"
#include "qhttpserverresponse.hpp"

#include "../../entities/entity_broadcaster/broadcaster.h"

using namespace qhttp::server;

namespace entities {
    class Broadcaster;
}

channels::BroadcasterHttp::BroadcasterHttp(QObject* parent)
    : BroadcasterChannel(parent),
      _server(nullptr)
{
}

bool channels::BroadcasterHttp::init()
{
    bool initialised = false;
    _server = new QHttpServer(this);
    if (_server) {
        initialised = _server->listen(QHostAddress::Any, 8081);
        connect(_server,&QHttpServer::newRequest,[=](QHttpRequest*, QHttpResponse* response){
            QJsonArray readingsJson;
            for (int i=0;i<_lastReadings.count();++i) {
                readingsJson.append(QJsonObject::fromVariantMap(_lastReadings.at(0)));
            }
            QByteArray message = QJsonDocument(readingsJson).toJson(QJsonDocument::Compact);
            response->end(message);
        });
    }
    return initialised;
}

void channels::BroadcasterHttp::sendReadings(QList<QVariantMap> readings)
{
    _lastReadings = readings;
}

