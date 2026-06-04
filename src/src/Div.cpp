#include "pch.h"
#include "../include/Div.h"

#include <algorithm>
#include <array>
#include <cctype>
#include <sstream>
#include <string>
#include <unordered_map>

namespace {

std::string trim(const std::string& value)
{
    std::size_t begin = 0;
    while (begin < value.size() && std::isspace(static_cast<unsigned char>(value[begin])))
        ++begin;

    std::size_t end = value.size();
    while (end > begin && std::isspace(static_cast<unsigned char>(value[end - 1])))
        --end;

    return value.substr(begin, end - begin);
}

std::string toLower(std::string value)
{
    std::transform(value.begin(), value.end(), value.begin(),
        [](unsigned char ch) { return static_cast<char>(std::tolower(ch)); });
    return value;
}

bool parseNonNegativeInt(const std::string& value, int& result)
{
    if (value.empty()) return false;

    std::size_t pos = 0;
    try {
        int parsed = std::stoi(value, &pos);
        if (pos != value.size() || parsed < 0)
            return false;
        result = parsed;
        return true;
    }
    catch (...) {
        return false;
    }
}

bool parseNamedColor(const std::string& value, COLORREF& color)
{
    static const std::unordered_map<std::string, COLORREF> colors{
        { "black", RGB(0, 0, 0) },
        { "white", RGB(255, 255, 255) },
        { "red", RGB(255, 0, 0) },
        { "green", RGB(0, 255, 0) },
        { "blue", RGB(0, 0, 255) },
    };

    auto it = colors.find(toLower(value));
    if (it == colors.end())
        return false;

    color = it->second;
    return true;
}

bool parseRgbColor(const std::string& value, COLORREF& color)
{
    if (value.size() < 7 || value.front() != '[' || value.back() != ']')
        return false;

    std::array<int, 3> rgb{};
    std::stringstream stream(value.substr(1, value.size() - 2));
    std::string part;
    int index = 0;

    while (std::getline(stream, part, ',')) {
        if (index >= 3)
            return false;

        int component = 0;
        if (!parseNonNegativeInt(trim(part), component) || component > 255)
            return false;

        rgb[index++] = component;
    }

    if (index != 3)
        return false;

    color = RGB(rgb[0], rgb[1], rgb[2]);
    return true;
}

} // namespace

namespace IrisGUI {

Div::Div(int w, int h)
    : Widget(w, h) {}

Div::Div(int x, int y, int w, int h)
    : Widget(x, y, w, h) {}

Div::Div(const std::string& className, int w, int h)
    : Widget(w, h)
{
    applyClassName(className);
}

Div::Div(int x, int y, int w, int h, const std::string& className)
    : Widget(x, y, w, h)
{
    applyClassName(className);
}

Div::Div(const std::string& className, const std::wstring& text, int w, int h)
    : Widget(w, h), m_text(text)
{
    applyClassName(className);
}

void Div::draw()
{
    if (!m_visible) return;

    const int left = m_x + m_style.margin.left;
    const int top = m_y + m_style.margin.top;
    const int right = ax() - m_style.margin.right;
    const int bottom = ay() - m_style.margin.bottom;

    setfillcolor(m_style.bgColor);
    if (m_style.borderRadius > 0)
        solidroundrect(left, top, right, bottom, m_style.borderRadius * 2, m_style.borderRadius * 2);
    else
        solidrectangle(left, top, right, bottom);

    // 背景图片
    if (m_bgImageLoaded) {
        putimage(left, top, right - left, bottom - top, &m_bgImage, 0, 0);
    }

    if (m_style.borderWidth > 0) {
        setlinecolor(m_style.borderColor);
        setlinestyle(PS_SOLID, m_style.borderWidth);
        if (m_style.borderRadius > 0)
            roundrect(left, top, right, bottom, m_style.borderRadius * 2, m_style.borderRadius * 2);
        else
            rectangle(left, top, right, bottom);
    }

    //文字输出
    if (!m_text.empty()) {
        RECT textRect{
        left + m_style.padding.left + m_style.borderWidth,
        top + m_style.padding.top + m_style.borderWidth,
        right - m_style.padding.right - m_style.borderWidth,
        bottom - m_style.padding.bottom - m_style.borderWidth
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
}

void Div::setClassName(const std::string& className)
{
    applyClassName(className);
}

const std::string& Div::className() const
{
    return m_className;
}

void Div::applyClassName(const std::string& className)
{
    m_className = className;

    WidgetStyle parsedStyle = style();
    int parsedWidth = width();
    int parsedHeight = height();

    setFlex(false);

    std::istringstream stream(className);
    std::string token;
    while (stream >> token) {
        switch (token[0]) {
        case 'f':
            if (token == "flex") {
                setFlex(true);
                break;
            }

            if (token.starts_with("font-")) {
                int value = 0;
                if (parseNonNegativeInt(token.substr(5), value))
                    parsedStyle.fontSize = value;
            }
            break;

        case 'w':
            if (token.starts_with("w-")) {
                int value = 0;
                if (parseNonNegativeInt(token.substr(2), value))
                    parsedWidth = value;
            }
            break;

        case 'h':
            if (token.starts_with("h-")) {
                int value = 0;
                if (parseNonNegativeInt(token.substr(2), value))
                    parsedHeight = value;
            }
            break;

        case 'm':
			if (token.starts_with("m-")) {
				int value = 0;
				if (parseNonNegativeInt(token.substr(2), value)) {
					parsedStyle.margin.left = value;
					parsedStyle.margin.top = value;
					parsedStyle.margin.right = value;
					parsedStyle.margin.bottom = value;
				}
				break;
			}

            if (token.size() <= 3 || token[2] != '-')
                break;

            {
                int value = 0;
                if (!parseNonNegativeInt(token.substr(3), value))
                    break;

                switch (token[1]) {
                case 'l':
                    parsedStyle.margin.left = value;
                    break;
                case 'r':
                    parsedStyle.margin.right = value;
                    break;
                case 'b':
                    parsedStyle.margin.bottom = value;
                    break;
                case 't':
                    parsedStyle.margin.top = value;
                    break;
                case 'x':
                    parsedStyle.margin.left = value;
                    parsedStyle.margin.right = value;
                    break;
                case 'y':
                    parsedStyle.margin.top = value;
                    parsedStyle.margin.bottom = value;
                    break;
                default:
                    break;
                }
            }
            break;

        case 'p':
            if (token.starts_with("p-")) {
                int value = 0;
                if (parseNonNegativeInt(token.substr(2), value)) {
                    parsedStyle.padding.left = value;
                    parsedStyle.padding.top = value;
                    parsedStyle.padding.right = value;
                    parsedStyle.padding.bottom = value;
                }
                break;
            }

            if (token.size() <= 3 || token[2] != '-')
                break;

            {
                int value = 0;
                if (!parseNonNegativeInt(token.substr(3), value))
                    break;

                switch (token[1]) {
                case 'l':
                    parsedStyle.padding.left = value;
                    break;
                case 'r':
                    parsedStyle.padding.right = value;
                    break;
                case 'b':
                    parsedStyle.padding.bottom = value;
                    break;
                case 't':
                    parsedStyle.padding.top = value;
                    break;
				case 'x':
					parsedStyle.padding.left = value;
					parsedStyle.padding.right = value;
					break;
				case 'y':
					parsedStyle.padding.top = value;
					parsedStyle.padding.bottom = value;
					break;
                default:
                    break;
                }
            }
            break;

        case 'b':
			if (token.starts_with("b-")) {
				int value = 0;
				if (parseNonNegativeInt(token.substr(2), value))
					parsedStyle.borderWidth = value;
			}
			else if (token.starts_with("border-")) {
				const std::string value = token.substr(7);
				COLORREF color = parsedStyle.borderColor;
				if (parseNamedColor(value, color) || parseRgbColor(value, color))
					parsedStyle.borderColor = color;
			}

            if (token.starts_with("bg-")) {
                const std::string value = token.substr(3);
                COLORREF color = parsedStyle.bgColor;
                if (parseNamedColor(value, color) || parseRgbColor(value, color)) {
                    parsedStyle.bgColor = color;
                }
                else if (value.size() > 2 && value.front() == '[' && value.back() == ']') {
                    // Image background: bg-[filename.png]
                    const std::string imagePath = value.substr(1, value.size() - 2);
                    const int len = MultiByteToWideChar(CP_UTF8, 0, imagePath.c_str(), -1, nullptr, 0);
                    std::wstring wPath(len, L'\0');
                    MultiByteToWideChar(CP_UTF8, 0, imagePath.c_str(), -1, &wPath[0], len);
                    int result = loadimage(&m_bgImage, wPath.c_str());
                    if(result == 0)
                        m_bgImageLoaded = true;
                }
            }
            break;

        case 'r':
			if (token.starts_with("round-")) {
				int value = 0;
				if (parseNonNegativeInt(token.substr(6), value))
					parsedStyle.borderRadius = value;
			}
            break;

        default:
            break;
        }
    }

    setSize(parsedWidth, parsedHeight);
    setStyle(parsedStyle);
}

} // namespace IrisGUI
