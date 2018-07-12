#include "panel.h"

namespace entities {
Panel::Panel(QObject *parent) : QObject(parent)
{
}

QSize Panel::get_size() const {
    return m_size;
}

void Panel::set_size(QSize size) {
    if (size != m_size) {
        m_size = size;
        emit sizeChanged();
    }
}
}
