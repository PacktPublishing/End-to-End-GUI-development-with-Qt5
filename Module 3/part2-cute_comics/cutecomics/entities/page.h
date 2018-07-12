#ifndef PAGE_H
#define PAGE_H

#include <QObject>
#include <QSize>

namespace entities {
class Panel;
class Page : public QObject
{
    Q_OBJECT
public:
    explicit Page(QObject *parent = nullptr);
    ~Page();
    QList<Panel*>* get_panels() const;
    QSize get_size() const;
    void set_size(QSize);

signals:
    void sizeChanged();

private:
    QList<Panel*>* m_panels = new QList<Panel*>();
    QSize m_size;
};
}

#endif // PAGE_H
