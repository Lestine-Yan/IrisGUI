#pragma once

#include "Widget.h"

namespace IrisGUI {

class App;

class Layout : public Widget {
public:
    Layout();
    Layout(int w, int h);

    App* app() const;

    void setPos(int x, int y);
    void setGeometry(int x, int y, int w, int h);

    void draw() override;

private:
    friend class App;

    void setApp(App* app);

    App* m_app = nullptr;
};

} // namespace IrisGUI
