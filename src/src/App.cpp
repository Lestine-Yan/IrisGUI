#include "pch.h"
#include "../include/App.h"

namespace IrisGUI {

App::App()
    : Widget(0, 0, 0, 0) {}

App::App(int w, int h)
    : Widget(0, 0, w, h) {}

void App::draw() {}

} // namespace IrisGUI
