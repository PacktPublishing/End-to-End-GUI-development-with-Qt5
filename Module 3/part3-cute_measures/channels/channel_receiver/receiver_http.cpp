// receiver_http.cpp
#include <QDebug>
#include "receiver_http.h"
#include <QVariantList>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>

namespace channels {
static const QUrl broadcasterHttpUrl("http://127.0.0.1:8081");
}

channels::ReceiverHttp::ReceiverHttp(QObject *parent) : ReceiverChannel(parent)
{
    qDebug() << Q_FUNC_INFO;
    _timer.setInterval(1000);
    _nam = new QNetworkAccessManager(this);
    connect(_nam, &QNetworkAccessManager::finished, this, &ReceiverHttp::_replyFinished);
    connect(&_timer, &QTimer::timeout, this, &ReceiverHttp::receiveReadings);
}

channels::ReceiverHttp::~ReceiverHttp()
{
    qDebug() << Q_FUNC_INFO;
    _timer.stop();
}

void channels::ReceiverHttp::init()
{
    qDebug() << Q_FUNC_INFO;
    _timer.start();
}

void channels::ReceiverHttp::receiveReadings()
{
    qDebug() << Q_FUNC_INFO;
    if (_nam) _nam->get(QNetworkRequest(channels::broadcasterHttpUrl));
}

void channels::ReceiverHttp::_replyFinished(QNetworkReply *reply)
{
    QByteArray readingsBytes = reply->readAll();
    QJsonDocument readingsDoc = QJsonDocument::fromJson(readingsBytes);
    QJsonArray readingsArray = readingsDoc.array();
    QVariantList readings;
    for (int i=0; i<readingsArray.count(); ++i) {
        readings.append(readingsArray.at(i).toObject().toVariantMap());
    }
    emit readingsProcessed(readings);
    reply->deleteLater();
}


