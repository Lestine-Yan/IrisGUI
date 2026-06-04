#pragma once

#include "Widget.h"
#include <string>

namespace IrisGUI {

class Div : public Widget {
public:
    Div(int w = 100, int h = 30);
    Div(int x, int y, int w, int h);
    Div(const std::string& className, int w = 100, int h = 30);
    Div(int x, int y, int w, int h, const std::string& className);
	Div(const std::string& className, const std::wstring& text, int w = 100, int h = 30);

    void draw() override;

    void setClassName(const std::string& className);
    const std::string& className() const;
    void applyClassName(const std::string& className);
    void setText(const std::wstring& text);

private:
    std::string m_className;
    std::wstring m_text;
};

} // namespace IrisGUI
