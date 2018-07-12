#ifndef ADD_PANEL_TO_PAGE_H
#define ADD_PANEL_TO_PAGE_H

#include <QObject>

#include "../entities/page.h"
#include "../entities/panel.h"

namespace usecases {
class AddPanelToPage : public QObject
{
    Q_OBJECT
public:
    explicit AddPanelToPage(QObject *parent = nullptr, entities::Page* page = nullptr);
    void run();

signals:
    void success();
    void failure();

private:
    entities::Page* m_page;
};
}

#endif // ADD_PANEL_TO_PAGE_H
