// cmmonitor/main.cpp
#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QTranslator>
#include <qtwebengineglobal.h>
#include <QtWebChannel>

#include "../channels/channel_receiver/receiver_bt.h"
#include "../channels/channel_receiver/receiver_http.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QApplication app(argc, argv);

    QTranslator translator;
//    QLocale::setDefault(QLocale("it_IT"));
    app.installTranslator(&translator);
    translator.load(QString(":/cmmonitor_%1.qm").arg(QLocale().name()));

    auto receiverChannel = new channels::ReceiverHttp(&app);
    QtWebEngine::initialize();
    qRegisterMetaType<QQmlWebChannel*>();
    auto defaultWebChannel = new QQmlWebChannel(&app);
    defaultWebChannel->registerObject(QStringLiteral("receiverChannel"), receiverChannel);

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("receiverChannel",receiverChannel);
    engine.rootContext()->setContextProperty("defaultWebChannel",defaultWebChannel);
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    receiverChannel->init();

    return app.exec();
}
