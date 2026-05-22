#pragma once

#include "Widget.h"
#include <string>

namespace IrisGUI {

class Root : public Widget {
public:
    Root(int w = 640, int h = 480, const std::wstring& title = L"IrisGUI");

    void draw() override;

    Root& mount(Widget* child);
    void end();

    bool isEnded() const { return m_ended; }

private:
    std::wstring m_title;
    bool m_ended = false;
};

} // namespace IrisGUI
