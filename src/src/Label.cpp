#include "pch.h"
#include "../include/Label.h"

namespace IrisGUI {

Label::Label(const std::wstring& text, int w, int h)
    : Div(w, h), m_text(text) {}

Label::Label(const std::string& className, const std::wstring& text, int w, int h)
    : Div(className, w, h), m_text(text) {}

Label::Label(int x, int y, int w, int h, const std::wstring& text)
    : Div(x, y, w, h), m_text(text) {}

Label::Label(int x, int y, int w, int h, const std::wstring& text, const std::string& className)
    : Div(x, y, w, h, className), m_text(text) {}

void Label::draw()
{
    if (!m_visible) return;

    Div::draw();

    const int left = absX() + m_style.margin.left;
    const int top = absY() + m_style.margin.top;
    const int right = left + m_width;
    const int bottom = top + m_height;

    RECT textRect{
        left + m_style.padding.left,
        top + m_style.padding.top,
        right - m_style.padding.right,
        bottom - m_style.padding.bottom
    };

    LOGFONT font{};
    font.lfHeight = m_style.fontSize;
    font.lfCharSet = DEFAULT_CHARSET;
    font.lfQuality = PROOF_QUALITY;
    wcscpy_s(font.lfFaceName, L"\x9ED1\x4F53");

    setbkmode(TRANSPARENT);
    settextcolor(m_style.textColor);
    settextstyle(&font);
    drawtext(m_text.c_str(), &textRect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
}

void Label::setText(const std::wstring& text)
{
    m_text = text;
}

const std::wstring& Label::text() const
{
    return m_text;
}

} // namespace IrisGUI
