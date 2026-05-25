#pragma once

#include "Widget.h"

namespace IrisGUI {

class App : public Widget {
public:
    App();
    App(int w, int h);

    void draw() override;
};

} // namespace IrisGUI
