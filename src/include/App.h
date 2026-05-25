#pragma once

#include "Widget.h"

namespace IrisGUI {

class Layout;

class App : public Widget {
public:
    App();
    App(int w, int h);
    ~App() override;

    App& layout(Layout* layout);
    Layout* layout() const;

    void draw() override;
    void update() override;

private:
    Layout* m_layout = nullptr;
};

} // namespace IrisGUI
