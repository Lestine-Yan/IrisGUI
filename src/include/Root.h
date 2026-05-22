#pragma once

#include "Widget.h"
#include <string>

namespace IrisGUI {

class Root : public Widget {
public:
    Root(const std::wstring& title = L"IrisGUI");
    Root(int w, int h, const std::wstring& title = L"IrisGUI");

    void draw() override;

    Root& mount(Widget* child);
    void end();

    bool isEnded() const { return m_ended; }

private:
    std::wstring m_title;
    bool m_ended = false;
    bool m_hasWindowSize = false;
};

} // namespace IrisGUI
