#include <QString>
#include <QtTest>

class Test_channel_receiver : public QObject
{
    Q_OBJECT

public:
    Test_channel_receiver();

private Q_SLOTS:
    void testCase1();
};

Test_channel_receiver::Test_channel_receiver()
{
}

void Test_channel_receiver::testCase1()
{
    QVERIFY2(true, "Failure");
}

QTEST_APPLESS_MAIN(Test_channel_receiver)

#include "tst_channel_receiver.moc"
