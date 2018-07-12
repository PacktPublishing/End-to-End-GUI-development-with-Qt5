// receiver_http.h
#ifndef RECEIVER_HTTP_H
#define RECEIVER_HTTP_H

#include <QObject>
#include <QTimer>

QT_FORWARD_DECLARE_CLASS(QNetworkAccessManager);
QT_FORWARD_DECLARE_CLASS(QNetworkReply);

#include "receiver_channel.h"

namespace channels {
class ReceiverHttp : public ReceiverChannel
{
    Q_OBJECT
public:
    explicit ReceiverHttp(QObject *parent = nullptr);
    ~ReceiverHttp();
    Q_INVOKABLE void init() override;
public slots:
    void receiveReadings() override;

private:
    QTimer _timer;
    QNetworkAccessManager* _nam;

    void _replyFinished(QNetworkReply* reply);
};
}

#endif // RECEIVER_HTTP_H
