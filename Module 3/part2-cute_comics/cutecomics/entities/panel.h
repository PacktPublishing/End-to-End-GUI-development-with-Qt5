#ifndef PANEL_H
#define PANEL_H

#include <QObject>
#include <QSize>

namespace entities {
class Panel : public QObject
{
    Q_OBJECT
public:
    explicit Panel(QObject *parent = nullptr);
    QSize get_size() const;
    void set_size(QSize size);
signals:
    void sizeChanged();

private:
    QSize m_size;
};
}
#endif // PANEL_H
