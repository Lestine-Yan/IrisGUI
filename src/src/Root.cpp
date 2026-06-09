#include "pch.h"
#include "../include/Root.h"
#include "../include/App.h"
#include "../include/Layout.h"
#include <typeinfo>

namespace IrisGUI {

Root::Root(const std::wstring& title)
    : Widget(0, 0), m_title(title) {}

Root::Root(int w, int h, const std::wstring& title)
    : Widget(0, 0, w, h), m_title(title), m_hasWindowSize(true) {}

void Root::draw()
{
    if (!m_visible) return;

    setfillcolor(m_style.bgColor);
    solidrectangle(0, 0, m_width, m_height);
}

Root& Root::mount(Widget* child)
{
    if (!m_ended) {
        if (auto* app = dynamic_cast<App*>(child)) {
            bool hasMountedApp = false;
            for (auto* existing : m_children) {
                if (existing != child && dynamic_cast<App*>(existing)) {
                    hasMountedApp = true;
                    break;
                }
            }

            app->setGeometry(0, 0, m_width, m_height);
            app->setVisible(!hasMountedApp);
        }

        attachChild(child);
    }
    return *this;
}

App& Root::app(std::size_t index)
{
    return dynamic_cast<App&>(*m_children.at(index));
}

const App& Root::app(std::size_t index) const
{
    return dynamic_cast<const App&>(*m_children.at(index));
}

std::size_t Root::appCount() const
{
    std::size_t count = 0;
    for (auto* child : m_children) {
        if (dynamic_cast<App*>(child))
            ++count;
    }
    return count;
}

void Root::end()
{
    if (m_ended) return;

    m_ended = true;

    const int windowWidth = m_hasWindowSize ? m_width : ax();
    const int windowHeight = m_hasWindowSize ? m_height : ay();

    if (!m_hasWindowSize) {
        m_width = windowWidth;
        m_height = windowHeight;
    }

    for (auto* child : m_children) {
        if (auto* app = dynamic_cast<App*>(child)) {
            app->setGeometry(0, 0, windowWidth, windowHeight);
            if (auto* layout = app->layout())
                layout->setGeometry(0, 0, windowWidth, windowHeight);
        }
    }

    initgraph(windowWidth, windowHeight);

    SetWindowTextW(GetHWnd(), m_title.c_str());

    BeginBatchDraw();

    bool running = true;
    while (running) {
        ExMessage msg{};
        while (peekmessage(&msg)) {
            if (msg.message == WM_CLOSE) {
                running = false;
                break;
            }

            bool dispatchedToLayout = false;
            for (auto it = m_children.rbegin(); it != m_children.rend(); ++it) {
                if (auto* app = dynamic_cast<App*>(*it)) {
                    if (app->isVisible()) {
                        if (auto* layout = app->layout()) {
                            if (layout->dispatchEventToChild(msg)) {
                                dispatchedToLayout = true;
                                break;
                            }
                        }
                        // 也尝试分发给 App 的直接子组件（如直接挂在 App 上的 Link）
                        if (!dispatchedToLayout && app->dispatchEventToChild(msg)) {
                            dispatchedToLayout = true;
                            break;
                        }
                    }
                }
            }

            if (!dispatchedToLayout)
                dispatchEvent(msg);
        }

        updateAll();
        setbkcolor(m_style.bgColor);
        cleardevice();
        drawAll();
        for (auto* child : m_children) {
            if (auto* app = dynamic_cast<App*>(child)) {
                if (app->isVisible()) {
                    if (auto* layout = app->layout())
                        layout->drawAll();
                }
            }
        }
        FlushBatchDraw();
        Sleep(16);
    }

    EndBatchDraw();
    closegraph();
}

} // namespace IrisGUI
