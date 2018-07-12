#include <QString>
#include <QtTest>

#include "../../entities/entity_broadcaster/broadcaster.h"

#include "broadcaster_bt.h"

class Test_channel_broadcasterBt : public QObject
{
    Q_OBJECT

public:
    Test_channel_broadcasterBt();

private Q_SLOTS:
    void init();
    void cleanup();
    void test_connectToBroadcaster();
private:
    channels::BroadcasterBt* _broadcaster_bt;
};

Test_channel_broadcasterBt::Test_channel_broadcasterBt()
{
}

void Test_channel_broadcasterBt::init()
{
    _broadcaster_bt = new channels::BroadcasterBt(this);
    QVERIFY(_broadcaster_bt->init());
}

void Test_channel_broadcasterBt::cleanup()
{
    delete _broadcaster_bt;
}

void Test_channel_broadcasterBt::test_connectToBroadcaster()
{
    auto broadcaster_entity = new entities::Broadcaster();
    QVERIFY(_broadcaster_bt->connectToBroadcaster(broadcaster_entity));
    delete broadcaster_entity;
}

QTEST_APPLESS_MAIN(Test_channel_broadcasterBt)

#include "tst_broadcaster_bt.moc"
