#include "pch.h"
#include "../include/App.h"
#include "../include/Layout.h"

namespace IrisGUI {

App::App()
    : Widget(0, 0, 0, 0) {}

App::App(int w, int h)
    : Widget(0, 0, w, h) {}

App::~App()
{
    delete m_layout;
}

App& App::layout(Layout* layout)
{
    if (m_layout == layout)
        return *this;

    delete m_layout;
    m_layout = layout;

    if (m_layout) {
        if (m_layout->parent())
            m_layout->setParent(nullptr);
        m_layout->setGeometry(0, 0, m_width, m_height);
    }

    return *this;
}

Layout* App::layout() const
{
    return m_layout;
}

void App::draw() {}

void App::update()
{
    if (m_layout)
        m_layout->updateAll();
}

} // namespace IrisGUI
