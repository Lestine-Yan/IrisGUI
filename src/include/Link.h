#pragma once

#include "Div.h"
#include <cstddef>
#include <string>

namespace IrisGUI {

class Link : public Div {
public:
    Link(std::size_t appIndex, int w = 100, int h = 30);
    Link(const std::string& className, std::size_t appIndex, int w = 100, int h = 30);

    void onMouseDown(const ExMessage& msg) override;

private:
    std::size_t m_appIndex = 0;
};

} // namespace IrisGUI
