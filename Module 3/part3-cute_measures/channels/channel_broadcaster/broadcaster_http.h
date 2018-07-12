// broadcaster_http.h
#ifndef BROADCASTER_HTTP_H
#define BROADCASTER_HTTP_H

#include "broadcaster_channel.h"

namespace qhttp { namespace server {
class QHttpServer;
}}

namespace channels {
class BroadcasterHttp : public BroadcasterChannel
{
public:
    explicit BroadcasterHttp(QObject* parent = nullptr);
    bool init() override;
public slots:
    void sendReadings(QList<QVariantMap> readings) override;

private:
    qhttp::server::QHttpServer* _server;
    QList<QVariantMap> _lastReadings;
};
}

#endif // BROADCASTER_HTTP_H
