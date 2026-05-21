#pragma once

#include "Widget.h"
#include <string>

namespace IrisGUI {

class Label : public Widget {
public:
    Label(int x = 0, int y = 0, int w = 100, int h = 30, const std::wstring& text = L"");

    void draw() override;

    void setText(const std::wstring& text);
    const std::wstring& text() const;

private:
    std::wstring m_text;
};

} // namespace IrisGUI
