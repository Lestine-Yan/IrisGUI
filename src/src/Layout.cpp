#include "pch.h"
#include "../include/Layout.h"

namespace IrisGUI {

Layout::Layout()
    : Widget(0, 0, 0, 0) {}

Layout::Layout(int w, int h)
    : Widget(0, 0, w, h) {}

void Layout::setPos(int, int)
{
    Widget::setPos(0, 0);
}

void Layout::setGeometry(int, int, int w, int h)
{
    Widget::setGeometry(0, 0, w, h);
}

void Layout::draw() {}

} // namespace IrisGUI
