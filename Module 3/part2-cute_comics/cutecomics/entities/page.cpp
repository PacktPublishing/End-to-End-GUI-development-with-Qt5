#include "page.h"
namespace entities {
Page::Page(QObject *parent) : QObject(parent)
{

}


Page::~Page()
{
    delete m_panels;
}

QList<Panel *>* Page::get_panels() const {
    return m_panels;
}

QSize Page::get_size() const {
    return m_size;
}

void Page::set_size(QSize size)
{
    if (size != m_size) {
        m_size = size;
        emit sizeChanged();
    }
}
}
