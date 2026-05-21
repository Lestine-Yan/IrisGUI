#include "pch.h"
#include "../include/Widget.h"

namespace IrisGUI {

Widget::Widget(int x, int y, int w, int h)
    : m_x(x), m_y(y), m_width(w), m_height(h) {}

Widget::~Widget()
{
    if (m_parent)
        m_parent->removeChild(this);

    for (auto* child : m_children)
        delete child;
    m_children.clear();
}

// ── Position & size ──────────────────────────────────────────────────

void Widget::setPos(int x, int y) { m_x = x; m_y = y; }
void Widget::setSize(int w, int h) { m_width = w; m_height = h; }
void Widget::setGeometry(int x, int y, int w, int h)
{
    m_x = x; m_y = y;
    m_width = w; m_height = h;
}

int Widget::absX() const
{
    int ax = m_x;
    for (const Widget* p = m_parent; p; p = p->m_parent)
        ax += p->m_x;
    return ax;
}

int Widget::absY() const
{
    int ay = m_y;
    for (const Widget* p = m_parent; p; p = p->m_parent)
        ay += p->m_y;
    return ay;
}

// ── Visibility ───────────────────────────────────────────────────────

void Widget::show()  { m_visible = true; }
void Widget::hide()  { m_visible = false; }
void Widget::setVisible(bool v) { m_visible = v; }

// ── Widget tree ──────────────────────────────────────────────────────

void Widget::addChild(Widget* child)
{
    if (!child) return;
    if (child->m_parent)
        child->m_parent->removeChild(child);
    child->m_parent = this;
    m_children.push_back(child);
}

void Widget::removeChild(Widget* child)
{
    if (!child) return;
    auto it = std::find(m_children.begin(), m_children.end(), child);
    if (it != m_children.end()) {
        m_children.erase(it);
        child->m_parent = nullptr;
    }
}

void Widget::setParent(Widget* parent)
{
    if (parent)
        parent->addChild(this);
    else if (m_parent)
        m_parent->removeChild(this);
}

// ── Hit testing ──────────────────────────────────────────────────────

bool Widget::containsPoint(int px, int py) const
{
    int ax = absX(), ay = absY();
    return px >= ax && px < ax + m_width &&
           py >= ay && py < ay + m_height;
}

// ── Event handling ───────────────────────────────────────────────────

void Widget::handleEvent(const ExMessage& msg)
{
    if (!m_visible) return;

    switch (msg.message) {
    case WM_LBUTTONDOWN:
    case WM_RBUTTONDOWN:
    case WM_MBUTTONDOWN:
        onMouseDown(msg);
        break;
    case WM_LBUTTONUP:
    case WM_RBUTTONUP:
    case WM_MBUTTONUP:
        onMouseUp(msg);
        break;
    case WM_MOUSEMOVE:
        onMouseMove(msg);
        break;
    }
}

// ── Static dispatch ──────────────────────────────────────────────────

void Widget::drawAll(Widget* root)
{
    if (!root || !root->m_visible) return;
    root->draw();
    for (auto* child : root->m_children)
        drawAll(child);
}

void Widget::updateAll(Widget* root)
{
    if (!root) return;
    root->update();
    for (auto* child : root->m_children)
        updateAll(child);
}

void Widget::dispatchEvent(Widget* root, const ExMessage& msg)
{
    if (!root || !root->m_visible) return;

    // Mouse events: dispatch to the topmost child that contains the point
    bool isMouseEvent = (msg.message == WM_LBUTTONDOWN ||
                         msg.message == WM_LBUTTONUP   ||
                         msg.message == WM_RBUTTONDOWN ||
                         msg.message == WM_RBUTTONUP   ||
                         msg.message == WM_MBUTTONDOWN ||
                         msg.message == WM_MBUTTONUP   ||
                         msg.message == WM_MOUSEMOVE   ||
                         msg.message == WM_MOUSEWHEEL);

    if (isMouseEvent) {
        for (auto it = root->m_children.rbegin();
             it != root->m_children.rend(); ++it) {
            if ((*it)->containsPoint(msg.x, msg.y)) {
                dispatchEvent(*it, msg);
                return;
            }
        }
    }

    root->handleEvent(msg);
}

} // namespace IrisGUI
