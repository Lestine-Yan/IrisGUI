#include "pch.h"
#include "../include/Root.h"

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
    if (!m_ended)
        addChild(child);
    return *this;
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
            dispatchEvent(msg);
        }

        updateAll();
        setbkcolor(m_style.bgColor);
        cleardevice();
        drawAll();
        FlushBatchDraw();
        Sleep(16);
    }

    EndBatchDraw();
    closegraph();
}

} // namespace IrisGUI
