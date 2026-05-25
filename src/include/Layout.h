#pragma once

#include "Widget.h"

namespace IrisGUI {

class Layout : public Widget {
public:
    Layout();
    Layout(int w, int h);

    void setPos(int x, int y);
    void setGeometry(int x, int y, int w, int h);

    void draw() override;
};

} // namespace IrisGUI
