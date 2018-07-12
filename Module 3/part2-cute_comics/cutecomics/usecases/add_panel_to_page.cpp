#include "add_panel_to_page.h"

namespace usecases {
AddPanelToPage::AddPanelToPage(QObject *parent, entities::Page *page) : QObject(parent)
{
    m_page = page;
}

void AddPanelToPage::run() {
    if (m_page) {
        auto panel = new entities::Panel(m_page);
        panel->set_size(m_page->get_size());
        m_page->get_panels()->append(panel);
        emit success();
    } else {
        emit failure();
    }
}
}
