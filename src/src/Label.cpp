#include "pch.h"
#include "../include/Label.h"

namespace IrisGUI {

Label::Label(const std::wstring& text, int w, int h)
    : Widget(w, h), m_text(text) {}

Label::Label(int x, int y, int w, int h, const std::wstring& text)
    : Widget(x, y, w, h), m_text(text) {}

void Label::draw()
{
    if (!m_visible) return;

    const int left = absX();
    const int top = absY();
    const int right = left + m_width;
    const int bottom = top + m_height;

    setfillcolor(m_style.bgColor);
    if (m_style.borderRadius > 0)
        solidroundrect(left, top, right, bottom, m_style.borderRadius * 2, m_style.borderRadius * 2);
    else
        solidrectangle(left, top, right, bottom);

    if (m_style.borderWidth > 0) {
        setlinecolor(m_style.borderColor);
        setlinestyle(PS_SOLID, m_style.borderWidth);
        if (m_style.borderRadius > 0)
            roundrect(left, top, right, bottom, m_style.borderRadius * 2, m_style.borderRadius * 2);
        else
            rectangle(left, top, right, bottom);
    }

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
    drawtext(m_text.c_str(), &textRect, DT_LEFT | DT_VCENTER | DT_SINGLELINE);
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
