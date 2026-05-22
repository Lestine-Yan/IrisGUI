#include "pch.h"
#include "../include/Root.h"

namespace IrisGUI {

Root::Root(int w, int h, const std::wstring& title)
    : Widget(0, 0, w, h), m_title(title) {}

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

    initgraph(m_width, m_height);

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
