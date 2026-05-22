#pragma once

#include "Widget.h"
#include <string>

namespace IrisGUI {

class Label : public Widget {
public:
    Label(const std::wstring& text = L"", int w = 100, int h = 30);
    Label(int x, int y, int w, int h, const std::wstring& text);

    void draw() override;

    void setText(const std::wstring& text);
    const std::wstring& text() const;

private:
    std::wstring m_text;
};

} // namespace IrisGUI
